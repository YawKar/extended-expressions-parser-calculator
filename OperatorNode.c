#include "OperatorNode.h"
#include "OperandsContainer.h"
#include <stdlib.h>

OperatorNode* newOperatorNode() {
	OperatorNode* operatorNode = (OperatorNode*)malloc(sizeof(OperatorNode));
	operatorNode->operands = newOperandsContainer();
	operatorNode->operatorType = PLUS_OP;
	return operatorNode;
}