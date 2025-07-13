// include/axl/core/concepts/mapping.h
typedef struct ConceptNode ConceptNode;
typedef struct ConceptEdge ConceptEdge;
typedef struct ConceptMap ConceptMap;

typedef enum {
    FLOW_ANCHOR_START,     // Beginning of concept flow
    FLOW_ANCHOR_TRANSFORM, // During transformation
    FLOW_ANCHOR_END        // End of concept flow
} FlowAnchorPoint;

typedef void (*FlowAnchorCallback)(
    ConceptNode* source,
    ConceptNode* target,
    void* user_data
);

// Register a flow anchor at specific point
int register_flow_anchor(
    ConceptMap* map,
    FlowAnchorPoint point,
    FlowAnchorCallback callback,
    void* user_data
);
