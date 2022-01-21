#ifndef _PARSER_HEADER
#define _PARSER_HEADER
#include "BaseNode.h"
#include "OperandsContainer.h"

void parseExpression(BaseNode* root, char* expression, int leftBorder, int rightBorder);
void parseArguments(char* expression, int leftBorder, int rightBorder, OperandsContainer* operandsContainer);
#endif