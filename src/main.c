#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "InputFunctions/InputFunctions.h"
#include "ExpressionFunctions/ExpressionFunctions.h"
#include "Nodes/BaseNode/BaseNode.h"
#include "Parser/Parser.h"
#include "EvaluateNodesFunctions/EvaluateNodesFunctions.h"
#include "VariablesTable/VariablesTable.h"
#include "StringFunctions/StringFunctions.h"

int main() {
	printf("Enter the expression:\n");
	char* rawExpression = getLine(stdin);
	int variablesNumber = 0;
	printf("Enter the number of variables:\n");
	scanf("%d%*c", &variablesNumber);
	VariablesTable* variablesTable = newVariablesTable();
	if (variablesNumber > 0) {
		printf("Enter one variable definition per line:\n");
		for (int varIndex = 0; varIndex < variablesNumber; ++varIndex) {
			char* currentVariableDefinition = getLine(stdin);
			char* prettifiedVariableDefinition = prettifyExpressionCopy(currentVariableDefinition);
			int allVariableDefinitionLength = strlen(prettifiedVariableDefinition);
			int variableNameLength = 0;
			for (int i = 0; i < allVariableDefinitionLength; ++i) {
				if (prettifiedVariableDefinition[i] == '=')
					break;
				++variableNameLength;
			}
			char* variableName = (char*)malloc(sizeof(char) * (variableNameLength + 1));
			for (int i = 0; i < variableNameLength; ++i)
				variableName[i] = prettifiedVariableDefinition[i];
			variableName[variableNameLength] = '\0';
			VariableNode* variableNode;
			if (isVariableInTable(variablesTable, variableName)) {
				variableNode = getVariableNodeFromTable(variablesTable, variableName);
			}
			else {
				addVariableNameToTable(variablesTable, variableName);
				variableNode = newVariableNode();
				variableNode->variableName = copyString(variableName);
				assignNodeForVariableInTable(variablesTable, variableName, variableNode);
			}
			BaseNode* variableDefinitionNode = newBaseNode();
			parseExpression(variableDefinitionNode, prettifiedVariableDefinition, variableNameLength + 1, allVariableDefinitionLength, variablesTable);
			addOperandToOperandsContainer(variableDefinitionNode, variableNode->operands);
		}
	}
	char* prettifiedExpression = prettifyExpressionCopy(rawExpression);
	int prettifiedExpressionLength = strlen(prettifiedExpression);
	BaseNode* computationalRoot = newBaseNode();
	parseExpression(computationalRoot, prettifiedExpression, 0, prettifiedExpressionLength, variablesTable);
	printf("Evaluation: %Lf\n", evaluateBaseNode(computationalRoot));
	return 0;
}
