#ifndef _STD_FUNCTION_NODE_HEADER
#define _STD_FUNCTION_NODE_HEADER
#include "StdFunctionTypes.h"
#include "OperandsContainer.h"

typedef struct StdFunctionNode StdFunctionNode;
struct StdFunctionNode {
    StdFunctionType stdFunctionType;
    OperandsContainer* operands;
};

StdFunctionNode* newStdFunctionNode();
#endif