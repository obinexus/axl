// src/core/runtime/event_bus.c
#include <axl/core/runtime/event_bus.h>
#include <stdlib.h>
#include <string.h>

typedef struct EventSubscriptionNode {
    EventSubscription subscription;
    struct EventSubscriptionNode* next;
} EventSubscriptionNode;

static EventSubscriptionNode* subscriptions = NULL;
static int next_subscription_id = 1;

bool event_bus_init(void) {
    subscriptions = NULL;
    next_subscription_id = 1;
    return true;
}

int event_bus_subscribe(EventHandler handler, void* user_data, 
                      EventType* event_types, size_t event_type_count) {
    if (!handler || !event_types || event_type_count == 0) {
        return -1;
    }
    
    // Create new subscription
    EventSubscriptionNode* node = malloc(sizeof(EventSubscriptionNode));
    if (!node) return -1;
    
    // Copy event types
    EventType* types_copy = malloc(sizeof(EventType) * event_type_count);
    if (!types_copy) {
        free(node);
        return -1;
    }
    
    memcpy(types_copy, event_types, sizeof(EventType) * event_type_count);
    
    // Initialize subscription
    node->subscription.handler = handler;
    node->subscription.user_data = user_data;
    node->subscription.event_types = types_copy;
    node->subscription.event_type_count = event_type_count;
    
    // Add to list
    node->next = subscriptions;
    subscriptions = node;
    
    return next_subscription_id++;
}

void event_bus_publish(const Event* event) {
    if (!event) return;
    
    EventSubscriptionNode* node = subscriptions;
    while (node) {
        // Check if subscription is interested in this event
        for (size_t i = 0; i < node->subscription.event_type_count; i++) {
            if (node->subscription.event_types[i] == event->type) {
                // Invoke handler
                node->subscription.handler(event, node->subscription.user_data);
                break;
            }
        }
        
        node = node->next;
    }
}
