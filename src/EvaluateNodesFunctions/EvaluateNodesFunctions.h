#ifndef _EVALUATE_NODES_FUNCTIONS_HEADER
#define _EVALUATE_NODES_FUNCTIONS_HEADER
#include "../Nodes/AllNodes.h"

long double evaluateBaseNode(BaseNode* baseNode);
long double evaluateNumberNode(NumberNode* numberNode);
long double evaluateOperatorNode(OperatorNode* operatorNode);
long double evaluateConstantNode(ConstantNode* constantNode);
long double evaluateStdFunctionNode(StdFunctionNode* stdFunctionNode);
long double evaluateVariableNode(VariableNode* variableNode);
#endif
