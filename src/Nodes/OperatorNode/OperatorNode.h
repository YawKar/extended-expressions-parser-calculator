#ifndef _OPERATOR_NODE_HEADER
#define _OPERATOR_NODE_HEADER
#include "../../EnumTypes/OperatorTypes.h"
#include "../../OperandsContainer/OperandsContainer.h"

typedef struct OperatorNode OperatorNode;
struct OperatorNode {
    OperatorType operatorType;
    OperandsContainer* operands;
};

OperatorNode* newOperatorNode();
#endif
