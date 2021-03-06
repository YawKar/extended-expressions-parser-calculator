#ifndef _VARIABLE_NODE_HEADER
#define _VARIABLE_NODE_HEADER
#include "../../OperandsContainer/OperandsContainer.h"

typedef struct VariableNode VariableNode;
struct VariableNode {
    char* variableName;
    OperandsContainer* operands;
};

VariableNode* newVariableNode();
#endif
