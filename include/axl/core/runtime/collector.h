// include/axl/core/runtime/collector.h
#ifndef AXL_COLLECTOR_H
#define AXL_COLLECTOR_H

#include <stdbool.h>
#include <axl/core/runtime/event_bus.h>

typedef struct Collector Collector;

/**
 * Create a new collector for event aggregation
 */
Collector* collector_create(void);

/**
 * Register the collector with the event bus
 */
bool collector_register(Collector* collector, EventType* event_types, size_t count);

/**
 * Process collected events
 */
void collector_process(Collector* collector);

/**
 * Destroy the collector and free resources
 */
void collector_destroy(Collector* collector);

#endif // AXL_COLLECTOR_H
