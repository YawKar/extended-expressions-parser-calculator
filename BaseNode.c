#include "BaseNode.h"
#include <stdlib.h>

BaseNode* newBaseNode() {
	BaseNode* baseNode = (BaseNode*)malloc(sizeof(BaseNode));
	baseNode->nodeType = NULL_NODE;
	baseNode->realNode = NULL;
}