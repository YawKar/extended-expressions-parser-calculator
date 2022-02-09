#include "Parser.h"
#include <stdlib.h>
#include "../ExpressionFunctions/ExpressionFunctions.h"
#include "../Nodes/AllNodes.h"
#include "../VariablesTable/VariablesTable.h"
#include "../StringFunctions/StringFunctions.h"

void parseArguments(char* expression, int leftBorder, int rightBorder, OperandsContainer* operandsContainer, VariablesTable* variablesTable) {
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
			parseExpression(newOperand, expression, lastCommaIndex + 1, i, variablesTable);
			lastCommaIndex = i;
		}
	}
	// Last argument
	BaseNode* newOperand = newBaseNode();
	addOperandToOperandsContainer(newOperand, operandsContainer);
	parseExpression(newOperand, expression, lastCommaIndex + 1, rightBorder - 1, variablesTable);
}

void parseExpression(BaseNode* root, char* expression, int leftBorder, int rightBorder, VariablesTable* variablesTable) {
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
		parseExpression(leftOperand, expression, leftBorder, highestOperatorIndex, variablesTable);
		parseExpression(rightOperand, expression, highestOperatorIndex + 1, rightBorder, variablesTable);
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
		parseArguments(expression, leftBorder, rightBorder, stdFunctionNode->operands, variablesTable);
	}
	else {
		// Variable Entry
		root->nodeType = VARIABLE_NODE;
		char* variableName = (char*)malloc(sizeof(char) * (rightBorder - leftBorder + 1));
		for (int i = leftBorder; i < rightBorder; ++i) {
			variableName[i - leftBorder] = expression[i];
		}
		variableName[rightBorder - leftBorder] = '\0';
		if (isVariableInTable(variablesTable, variableName)) {
			root->realNode = (void*)getVariableNodeFromTable(variablesTable, variableName);
		}
		else {
			addVariableNameToTable(variablesTable, variableName);
			VariableNode* variableNode = newVariableNode();
			variableNode->variableName = copyString(variableName);
			assignNodeForVariableInTable(variablesTable, variableName, variableNode);
			root->realNode = (void*)variableNode;
		}
	}
}
