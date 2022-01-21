#include <string.h>
#include <stdio.h>
#include "InputFunctions.h"
#include "ExpressionFunctions.h"
#include "BaseNode.h"
#include "Parser.h"
#include "EvaluateNodesFunctions.h"

int main() {
	char* rawExpression = getLine();
	char* prettifiedExpression = prettifyExpressionCopy(rawExpression);
	int prettifiedExpressionLength = strlen(prettifiedExpression);
	BaseNode* computationalRoot = newBaseNode();
	parseExpression(computationalRoot, prettifiedExpression, 0, prettifiedExpressionLength);
	printf("Evaluation: %Lf\n", evaluateBaseNode(computationalRoot));
	return 0;
}