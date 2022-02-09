#ifndef _CONSTANT_NODE_HEADER
#define _CONSTANT_NODE_HEADER
#include "../../EnumTypes/ConstantTypes.h"

typedef struct ConstantNode ConstantNode;
struct ConstantNode {
    ConstantType constantType;
};

ConstantNode* newConstantNode();
#endif
