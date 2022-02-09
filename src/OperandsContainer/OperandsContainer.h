#ifndef _OPERANDS_CONTAINER_HEADER
#define _OPERANDS_CONTAINER_HEADER
#include "../Nodes/BaseNode/BaseNode.h"

typedef struct OperandsContainer OperandsContainer;
struct OperandsContainer {
    BaseNode** operands;
    int operandsNumber;
};

OperandsContainer* newOperandsContainer();
void addOperandToOperandsContainer(BaseNode* leftOperand, OperandsContainer* operandsContainer);
#endif
