#ifndef _EXPRESSION_FUNCTIONS_HEADER
#define _EXPRESSION_FUNCTIONS_HEADER
#include "OperatorTypes.h"
#include "ConstantTypes.h"
#include "StdFunctionTypes.h"

char* prettifyExpressionCopy(char* expression);
int isForbiddenCharacter(char ch);
int isExpressionBracketed(char* expression, int leftBorder, int rightBorder);
int countEndsBrackets(char* expression, int leftBorder, int rightBorder);
int doesExpressionHaveOperatorOnTop(char* expression, int leftBorder, int rightBorder);
int getHighestOperatorIndex(char* expression, int leftBorder, int rightBorder);
int doesExpressionContainNumberOnTop(char* expression, int leftBorder, int rightBorder);
long double parseNumber(char* expression, int leftBorder, int rightBorder);
int doesExpressionContainConstantOnTop(char* expression, int leftBorder, int rightBorder);
int doesExpressionContainStdFunctionOnTop(char* expression, int leftBorder, int rightBorder);
OperatorType getOperatorType(char ch); 
ConstantType getConstantType(char* expression, int leftBorder, int rightBorder);
StdFunctionType getStdFunctionType(char* expression, int leftBorder, int rightBorder);
#endif