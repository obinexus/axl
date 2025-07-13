// include/axl/core/axml/parser.h
#ifndef AXL_AXML_PARSER_H
#define AXL_AXML_PARSER_H

#include <stdbool.h>
#include <axl/core/utils/memory.h>

typedef enum {
    BUST_IMMEDIATE,
    BUST_DELAYED,
    BUST_CONDITIONAL
} BustPolicy;

typedef enum {
    CARDINALITY_ZERO_ONE,    // 0:1
    CARDINALITY_ONE_ZERO,    // 1:0
    CARDINALITY_ONE_ONE,     // 1:1
    CARDINALITY_ONE_MANY,    // 1:N
    CARDINALITY_MANY_ONE,    // N:1
    CARDINALITY_MANY_MANY    // N:M
} CardinalityType;

typedef struct AxmlBinding {
    char* name;
    char* value;
    char** values;
    size_t value_count;
    CardinalityType cardinality;
    struct AxmlBinding* next;
} AxmlBinding;

typedef struct AxmlConcept {
    char* id;
    AxmlBinding* bindings;
    struct AxmlConcept* next;
} AxmlConcept;

typedef struct AxmlSymbol {
    char* id;
    char* visual;
    struct AxmlSymbol* next;
} AxmlSymbol;

typedef struct AxmlConfig {
    char* source_path;
    BustPolicy bust_policy;
    bool retain_memory;
    AxmlConcept* concepts;
    AxmlSymbol* symbols;
} AxmlConfig;

/**
 * Parse an AXML configuration file
 */
AxmlConfig* axml_parse_file(const char* filename);

/**
 * Free AXML configuration resources
 */
void axml_free_config(AxmlConfig* config);

#endif // AXL_AXML_PARSER_H
