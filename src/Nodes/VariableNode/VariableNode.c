#include "VariableNode.h"
#include <stdlib.h>

VariableNode* newVariableNode() {
	VariableNode* variableNode = (VariableNode*)malloc(sizeof(VariableNode));
	variableNode->variableName = NULL;
	variableNode->operands = newOperandsContainer();
	return variableNode;
}