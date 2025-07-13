#ifndef AXL_DAG_H
#define AXL_DAG_H

#include <stddef.h>
#include <stddef.h>
#include <axl/core/token.h>     // For TokenType
#include <axl/core/taxonomy.h>  // For TaxonomyCategory

// Forward declarations
typedef enum TokenType TokenType;
typedef enum TaxonomyCategory TaxonomyCategory;




/// Resolution states for semantic nodes.
typedef enum {
    STATE_UNKNOWN = 0,
    STATE_TRUE,
    STATE_FALSE
} TruthValue;

/// Edge in the semantic DAG.
typedef struct DAGEdge {
    struct DAGNode *target;
    float           weight;    // Carries source node's weight
} DAGEdge;

/// Node in the semantic DAG.
/// One-to-one with a matched trie node.
typedef struct DAGNode {
    TokenType        type;         // LET, IDENT, ASSIGN, LITERAL, etc.
    TaxonomyCategory category;     // Verb–noun tag
    TruthValue       state;        // Resolved truth value
    DAGEdge         *in_edges;     // Array of incoming edges
    size_t           in_count;
    DAGEdge         *out_edges;    // Array of outgoing edges
    size_t           out_count;
} DAGNode;

/// Create an empty DAG node.
DAGNode*    dag_node_create(TokenType t,
                            TaxonomyCategory cat);

/// Link `from` → `to` with given weight.
void        dag_add_edge(DAGNode *from,
                         DAGNode *to,
                         float weight);

/// Topologically resolve all nodes' truth values.
void        dag_resolve(DAGNode *nodes[],
                        size_t node_count);

/// Initialize the DAG subsystem
int         dag_init(void);

#endif // AXL_DAG_H
