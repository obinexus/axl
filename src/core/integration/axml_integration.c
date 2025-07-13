// src/core/integration/axml_integration.c
#include <axl/core/integration/trie_dag.h>
#include <axl/core/axml/parser.h>

bool apply_axml_to_dag(DAGNode* root, AxmlConfig* config) {
    if (!root || !config) return false;
    
    // Apply concept bindings to DAG nodes
    AxmlConcept* concept = config->concepts;
    while (concept) {
        // Find DAG node matching concept ID
        DAGNode* concept_node = find_dag_node_by_id(root, concept->id);
        if (concept_node) {
            // Apply bindings
            AxmlBinding* binding = concept->bindings;
            while (binding) {
                apply_binding_to_node(concept_node, binding);
                binding = binding->next;
            }
        }
        
        concept = concept->next;
    }
    
    return true;
}

// Enhanced execute_axl_with_busting with AXML integration
bool execute_axl_with_busting(const char* axl_path, const char* axml_path) {
    // Parse AXML configuration
    AxmlConfig* config = axml_parse_file(axml_path);
    if (!config) {
        fprintf(stderr, "Failed to parse AXML configuration: %s\n", axml_path);
        return false;
    }
    
    // Create DAG buster
    DAGBuster* buster = dag_buster_create();
    if (!buster) {
        axml_free_config(config);
        return false;
    }
    
    // Load and parse AXL file
    FILE* axl_file = fopen(axl_path, "r");
    if (!axl_file) {
        fprintf(stderr, "Failed to open AXL file: %s\n", axl_path);
        axml_free_config(config);
        free(buster);
        return false;
    }
    
    // Read AXL content
    fseek(axl_file, 0, SEEK_END);
    long file_size = ftell(axl_file);
    rewind(axl_file);
    
    char* axl_content = (char*)malloc(file_size + 1);
    if (!axl_content) {
        fclose(axl_file);
        axml_free_config(config);
        free(buster);
        return false;
    }
    
    fread(axl_content, 1, file_size, axl_file);
    axl_content[file_size] = '\0';
    fclose(axl_file);
    
    // Parse AXL content to extract patterns
    buster->patterns = parse_axl_patterns(axl_content, &buster->pattern_count);
    free(axl_content);
    
    if (!buster->patterns) {
        fprintf(stderr, "Failed to parse AXL patterns\n");
        axml_free_config(config);
        free(buster);
        return false;
    }
    
    // Build semantic DAG
    buster->resolved_root = build_semantic_dag(buster->patterns, buster->pattern_count);
    if (!buster->resolved_root) {
        fprintf(stderr, "Failed to build semantic DAG\n");
        for (size_t i = 0; i < buster->pattern_count; i++) {
            free_trie_node(buster->patterns[i]);
        }
        free(buster->patterns);
        axml_free_config(config);
        free(buster);
        return false;
    }
    
    // Apply AXML configuration to DAG
    apply_axml_to_dag(buster->resolved_root, config);
    
    // Execute DAG
    bool result = execute_dag(buster->resolved_root);
    
    // Determine if we should destroy the DAG
    bool should_destroy = (config->bust_policy == BUST_IMMEDIATE) || !config->retain_memory;
    
    // Clean up
    if (should_destroy) {
        destroy_semantic_dag(buster->resolved_root);
        buster->resolved_root = NULL;
    }
    
    // Free patterns
    for (size_t i = 0; i < buster->pattern_count; i++) {
        free_trie_node(buster->patterns[i]);
    }
    free(buster->patterns);
    buster->patterns = NULL;
    buster->pattern_count = 0;
    
    // Free resources
    axml_free_config(config);
    free(buster);
    
    return result;
}
