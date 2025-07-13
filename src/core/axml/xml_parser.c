// src/core/axml/xml_parser.c
#include <axl/core/axml/parser.h>
#include <string.h>
#include <stdio.h>

// Forward declarations for our SAX-style parser
static void start_element_handler(void* user_data, const char* name, const char** attrs);
static void end_element_handler(void* user_data, const char* name);
static void character_data_handler(void* user_data, const char* data, int length);

AxmlConfig* axml_parse_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }
    
    // Initialize config structure
    AxmlConfig* config = (AxmlConfig*)calloc(1, sizeof(AxmlConfig));
    if (!config) {
        fclose(file);
        return NULL;
    }
    
    // Default values
    config->bust_policy = BUST_IMMEDIATE;
    config->retain_memory = false;
    
    // Set up XML parser
    // Implementation detail: We would use a lightweight SAX parser here
    // like expat or a minimal custom implementation
    
    // For this code sketch, we'll assume the parsing succeeds
    // and manually populate a sample config
    
    // Sample initialization (in real code, this would come from XML parsing)
    config->source_path = strdup("main.axl");
    
    // Create sample concept
    AxmlConcept* concept = (AxmlConcept*)calloc(1, sizeof(AxmlConcept));
    concept->id = strdup("masquerade");
    
    // Create sample binding
    AxmlBinding* binding = (AxmlBinding*)calloc(1, sizeof(AxmlBinding));
    binding->name = strdup("chant");
    binding->value = strdup("Kwenu!");
    binding->cardinality = CARDINALITY_ONE_MANY;
    concept->bindings = binding;
    
    config->concepts = concept;
    
    // Clean up
    fclose(file);
    
    return config;
}

void axml_free_config(AxmlConfig* config) {
    if (!config) return;
    
    // Free source path
    free(config->source_path);
    
    // Free concepts and bindings
    AxmlConcept* concept = config->concepts;
    while (concept) {
        AxmlBinding* binding = concept->bindings;
        while (binding) {
            AxmlBinding* next_binding = binding->next;
            free(binding->name);
            free(binding->value);
            if (binding->values) {
                for (size_t i = 0; i < binding->value_count; i++) {
                    free(binding->values[i]);
                }
                free(binding->values);
            }
            free(binding);
            binding = next_binding;
        }
        
        AxmlConcept* next_concept = concept->next;
        free(concept->id);
        free(concept);
        concept = next_concept;
    }
    
    // Free symbols
    AxmlSymbol* symbol = config->symbols;
    while (symbol) {
        AxmlSymbol* next_symbol = symbol->next;
        free(symbol->id);
        free(symbol->visual);
        free(symbol);
        symbol = next_symbol;
    }
    
    // Free config
    free(config);
}
