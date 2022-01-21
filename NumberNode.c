#include "NumberNode.h"
#include <stdlib.h>

NumberNode* newNumberNode() {
	NumberNode* numberNode = (NumberNode*)malloc(sizeof(NumberNode));
	numberNode->number = 0L;
	return numberNode;
}