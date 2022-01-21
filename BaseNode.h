#ifndef _BASE_NODE_HEADER
#define _BASE_NODE_HEADER
#include "NodeTypes.h"

typedef struct BaseNode BaseNode;
struct BaseNode {
    NodeType nodeType;
    void* realNode;
};

BaseNode* newBaseNode();
#endif