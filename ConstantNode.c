#include "ConstantNode.h"
#include <stdlib.h>

ConstantNode* newConstantNode() {
	ConstantNode* constantNode = (ConstantNode*)malloc(sizeof(ConstantNode));
	constantNode->constantType = PI_NUMBER_CONSTANT;
	return constantNode;
}