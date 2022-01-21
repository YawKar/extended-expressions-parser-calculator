#include "Parser.h"
#include "ExpressionFunctions.h"
#include "OperatorNode.h"
#include "NumberNode.h"
#include "ConstantNode.h"
#include "StdFunctionNode.h"

void parseArguments(char* expression, int leftBorder, int rightBorder, OperandsContainer* operandsContainer) {
	int openBracketIndex = -1;
	for (int i = leftBorder; i < rightBorder; ++i) {
		if (expression[i] == '(') {
			openBracketIndex = i;
			break;
		}
	}
	int lastCommaIndex = openBracketIndex;
	int currentLevel = 0;
	for (int i = openBracketIndex + 1; i < rightBorder - 1; ++i) {
		if (expression[i] == '(') {
			++currentLevel;
			continue;
		}
		if (expression[i] == ')') {
			--currentLevel;
			continue;
		}
		if (currentLevel != 0)
			continue;
		if (expression[i] == ',') {
			// Found argument
			BaseNode* newOperand = newBaseNode();
			addOperandToOperandsContainer(newOperand, operandsContainer);
			parseExpression(newOperand, expression, lastCommaIndex + 1, i);
			lastCommaIndex = i;
		}
	}
	// Last argument
	BaseNode* newOperand = newBaseNode();
	addOperandToOperandsContainer(newOperand, operandsContainer);
	parseExpression(newOperand, expression, lastCommaIndex + 1, rightBorder - 1);
}

void parseExpression(BaseNode* root, char* expression, int leftBorder, int rightBorder) {
	if (isExpressionBracketed(expression, leftBorder, rightBorder)) {
		int endsBracketsNumber = countEndsBrackets(expression, leftBorder, rightBorder);
		leftBorder += endsBracketsNumber;
		rightBorder -= endsBracketsNumber;
	}

	if (doesExpressionHaveOperatorOnTop(expression, leftBorder, rightBorder)) {
		// Operator Node Entry
		root->nodeType = OPERATOR_NODE;
		int highestOperatorIndex = getHighestOperatorIndex(expression, leftBorder, rightBorder);
		OperatorType highestOperator = getOperatorType(expression[highestOperatorIndex]);
		OperatorNode* operatorNode = newOperatorNode();
		root->realNode = (void*)operatorNode;
		operatorNode->operatorType = highestOperator;
		BaseNode* leftOperand = newBaseNode();
		BaseNode* rightOperand = newBaseNode();
		addOperandToOperandsContainer(leftOperand, operatorNode->operands);
		addOperandToOperandsContainer(rightOperand, operatorNode->operands);
		parseExpression(leftOperand, expression, leftBorder, highestOperatorIndex);
		parseExpression(rightOperand, expression, highestOperatorIndex + 1, rightBorder);
	}
	else if (doesExpressionContainNumberOnTop(expression, leftBorder, rightBorder)) {
		// Number Node Entry
		root->nodeType = NUMBER_NODE;
		long double parsedNumber = parseNumber(expression, leftBorder, rightBorder);
		NumberNode* numberNode = newNumberNode();
		root->realNode = (void*)numberNode;
		numberNode->number = parsedNumber;
	}
	else if (doesExpressionContainConstantOnTop(expression, leftBorder, rightBorder)) {
		// Constant Node Entry
		root->nodeType = CONSTANT_NODE;
		ConstantNode* constantNode = newConstantNode();
		root->realNode = (void*)constantNode;
		constantNode->constantType = getConstantType(expression, leftBorder, rightBorder);
	}
	else if (doesExpressionContainStdFunctionOnTop(expression, leftBorder, rightBorder)) {
		// StdFunction Entry
		root->nodeType = STDFUNCTION_NODE;
		StdFunctionNode* stdFunctionNode = newStdFunctionNode();
		root->realNode = (void*)stdFunctionNode;
		stdFunctionNode->operands = newOperandsContainer();
		stdFunctionNode->stdFunctionType = getStdFunctionType(expression, leftBorder, rightBorder);
		parseArguments(expression, leftBorder, rightBorder, stdFunctionNode->operands);
	}
}