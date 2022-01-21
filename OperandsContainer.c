#include "OperandsContainer.h"
#include <stdlib.h>

OperandsContainer* newOperandsContainer() {
	OperandsContainer* operandsContainer = (OperandsContainer*)malloc(sizeof(OperandsContainer));
	operandsContainer->operands = NULL;
	operandsContainer->operandsNumber = 0;
	return operandsContainer;
}

void addOperandToOperandsContainer(BaseNode* newOperand, OperandsContainer* operandsContainer) {
	BaseNode** newOperands = (BaseNode**)malloc(sizeof(BaseNode*) * (operandsContainer->operandsNumber + 1));
	for (int i = 0; i < operandsContainer->operandsNumber; ++i) {
		newOperands[i] = operandsContainer->operands[i];
	}
	newOperands[operandsContainer->operandsNumber] = newOperand;
	++operandsContainer->operandsNumber;
	if (operandsContainer->operands != NULL)
		free(operandsContainer->operands);
	operandsContainer->operands = newOperands;
}