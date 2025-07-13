// include/axl/core/runtime/event_bus.h
#ifndef AXL_EVENT_BUS_H
#define AXL_EVENT_BUS_H

#include <stdbool.h>

typedef enum {
    EVENT_DAG_NODE_CREATED,
    EVENT_DAG_NODE_RESOLVED,
    EVENT_DAG_NODE_BUSTED,
    EVENT_TRIE_MATCH,
    EVENT_CACHE_MISS,
    EVENT_CACHE_HIT
} EventType;

typedef struct {
    EventType type;
    void* source;
    void* data;
    size_t data_size;
} Event;

typedef void (*EventHandler)(const Event* event, void* user_data);

typedef struct {
    EventHandler handler;
    void* user_data;
    EventType* event_types;
    size_t event_type_count;
} EventSubscription;

/**
 * Initialize the event bus system
 */
bool event_bus_init(void);

/**
 * Subscribe to specific events
 */
int event_bus_subscribe(EventHandler handler, void* user_data, 
                        EventType* event_types, size_t event_type_count);

/**
 * Unsubscribe from events
 */
void event_bus_unsubscribe(int subscription_id);

/**
 * Publish an event to all subscribers
 */
void event_bus_publish(const Event* event);

/**
 * Clean up the event bus system
 */
void event_bus_cleanup(void);

#endif // AXL_EVENT_BUS_H
