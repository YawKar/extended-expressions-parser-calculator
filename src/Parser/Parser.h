#ifndef _PARSER_HEADER
#define _PARSER_HEADER
#include "../Nodes/BaseNode/BaseNode.h"
#include "../OperandsContainer/OperandsContainer.h"
#include "../VariablesTable/VariablesTable.h"

void parseExpression(BaseNode* root, char* expression, int leftBorder, int rightBorder, VariablesTable* variablesTable);
void parseArguments(char* expression, int leftBorder, int rightBorder, OperandsContainer* operandsContainer, VariablesTable* variablesTable);
#endif
