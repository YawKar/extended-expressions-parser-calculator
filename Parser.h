#ifndef _PARSER_HEADER
#define _PARSER_HEADER
#include "BaseNode.h"
#include "OperandsContainer.h"
#include "VariablesTable.h"

void parseExpression(BaseNode* root, char* expression, int leftBorder, int rightBorder, VariablesTable* variablesTable);
void parseArguments(char* expression, int leftBorder, int rightBorder, OperandsContainer* operandsContainer, VariablesTable* variablesTable);
#endif