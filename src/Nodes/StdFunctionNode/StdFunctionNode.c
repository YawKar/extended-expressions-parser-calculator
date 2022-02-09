#include "StdFunctionNode.h"
#include <stdlib.h>

StdFunctionNode* newStdFunctionNode() {
	StdFunctionNode* stdFunctionNode = (StdFunctionNode*)malloc(sizeof(StdFunctionNode));
	stdFunctionNode->stdFunctionType = SIN_FUNC;
	stdFunctionNode->operands = newOperandsContainer();
	return stdFunctionNode;
}