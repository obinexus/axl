#ifndef AXL_TRIE_H
#define AXL_TRIE_H

#include <stdbool.h>
#include <regex.h>
#include <axl/core/taxonomy.h>
#include <stdbool.h>
#include <regex.h>

/// A node in the regex-bound trie.
/// Each node matches a regex pattern (e.g. "let|const").
typedef struct TrieNode {
    char           *pattern_str;     // Raw regex string
    regex_t         pattern;         // Compiled regex
    bool            terminal;        // Marks end of a token pattern
    float           weight;          // Semantic ranking weight
    TaxonomyCategory category;       // Verb–noun classification
    struct TrieNode *children[256];  // ASCII-indexed child pointers
} TrieNode;

/// Allocate and compile a new trie node.
/// pattern_str must outlive the node.
TrieNode*   trie_node_create(const char *pattern_str,
                             TaxonomyCategory cat,
                             float weight);

/// Insert a pattern into the trie (recursively compiles sub-patterns).
void        trie_insert(TrieNode *root,
                        const char *pattern_str,
                        TaxonomyCategory cat,
                        float weight);

/// Match `text[0..len)` against node->pattern.
bool        trie_match_node(TrieNode *node,
                            const char *text,
                            size_t len);

/// Initialize the trie subsystem
int         trie_init(void);

#endif // AXL_TRIE_H
