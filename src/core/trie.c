#include "axl/trie.h"
#include <stdlib.h>
#include <string.h>

TrieNode* trie_node_create(const char *pattern_str,
                           TaxonomyCategory cat,
                           float weight) {
    TrieNode *node = (TrieNode*)calloc(1, sizeof(TrieNode));
    if (!node) return NULL;
    
    node->pattern_str = strdup(pattern_str);
    node->category = cat;
    node->weight = weight;
    node->terminal = false;
    
    // Compile the regex pattern
    if (regcomp(&node->pattern, pattern_str, REG_EXTENDED) != 0) {
        free(node->pattern_str);
        free(node);
        return NULL;
    }
    
    return node;
}

bool trie_match_node(TrieNode *node, const char *text, size_t len) {
    if (!node || !text || len == 0) {
        return false;
    }
    
    // Create a null-terminated copy of the text segment for regex matching
    char *text_copy = (char *)malloc(len + 1);
    if (!text_copy) {
        return false;
    }
    
    memcpy(text_copy, text, len);
    text_copy[len] = '\0';
    
    // Execute the compiled regex against the text
    regmatch_t match;
    int result = regexec(&node->pattern, text_copy, 1, &match, 0);
    
    // Check if we have a match at the start of the string that consumes the entire input
    bool matches = (result == 0 && match.rm_so == 0 && match.rm_eo == len);
    
    free(text_copy);
    return matches;
}

void trie_insert(TrieNode *root,
                 const char *pattern_str,
                 TaxonomyCategory cat,
                 float weight) {
    // Implementation of pattern insertion logic
    // ...
}
