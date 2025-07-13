// src/core/runtime/collector.c
#include <axl/core/runtime/collector.h>
#include <stdlib.h>

#define MAX_EVENTS 1024

struct Collector {
    Event events[MAX_EVENTS];
    size_t event_count;
    int subscription_id;
};

static void collector_event_handler(const Event* event, void* user_data) {
    Collector* collector = (Collector*)user_data;
    
    // Store event if there's space
    if (collector->event_count < MAX_EVENTS) {
        // Deep copy of event
        collector->events[collector->event_count] = *event;
        
        // If data exists, make a copy
        if (event->data && event->data_size > 0) {
            void* data_copy = malloc(event->data_size);
            if (data_copy) {
                memcpy(data_copy, event->data, event->data_size);
                collector->events[collector->event_count].data = data_copy;
            }
        }
        
        collector->event_count++;
    }
}

Collector* collector_create(void) {
    Collector* collector = malloc(sizeof(Collector));
    if (!collector) return NULL;
    
    collector->event_count = 0;
    collector->subscription_id = -1;
    
    return collector;
}

bool collector_register(Collector* collector, EventType* event_types, size_t count) {
    if (!collector || !event_types || count == 0) return false;
    
    // Subscribe to events
    collector->subscription_id = event_bus_subscribe(
        collector_event_handler,
        collector,
        event_types,
        count
    );
    
    return collector->subscription_id >= 0;
}

void collector_process(Collector* collector) {
    if (!collector) return;
    
    // Process all collected events
    for (size_t i = 0; i < collector->event_count; i++) {
        Event* event = &collector->events[i];
        
        // Process based on event type
        switch (event->type) {
            case EVENT_DAG_NODE_CREATED:
                // Process node creation
                break;
                
            case EVENT_DAG_NODE_RESOLVED:
                // Process node resolution
                break;
                
            case EVENT_DAG_NODE_BUSTED:
                // Process node busting
                break;
                
            case EVENT_TRIE_MATCH:
                // Process trie match
                break;
                
            case EVENT_CACHE_MISS:
                // Process cache miss
                break;
                
            case EVENT_CACHE_HIT:
                // Process cache hit
                break;
        }
        
        // Free data if needed
        if (event->data) {
            free(event->data);
            event->data = NULL;
        }
    }
    
    // Reset event count
    collector->event_count = 0;
}

void collector_destroy(Collector* collector) {
    if (!collector) return;
    
    // Unsubscribe from events
    if (collector->subscription_id >= 0) {
        event_bus_unsubscribe(collector->subscription_id);
    }
    
    // Free any remaining event data
    for (size_t i = 0; i < collector->event_count; i++) {
        if (collector->events[i].data) {
            free(collector->events[i].data);
        }
    }
    
    free(collector);
}
