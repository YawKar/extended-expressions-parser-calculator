#include "EvaluateNodesFunctions.h"
#define _USE_MATH_DEFINES
#include <math.h>

long double evaluateNumberNode(NumberNode* numberNode) {
	return numberNode->number;
}

long double evaluateOperatorNode(OperatorNode* operatorNode) {
	long double leftOperand = evaluateBaseNode(operatorNode->operands->operands[0]);
	long double rightOperand = evaluateBaseNode(operatorNode->operands->operands[1]);
	switch (operatorNode->operatorType) {
		case PLUS_OP:
			return leftOperand + rightOperand;
		case MINUS_OP:
			return leftOperand - rightOperand;
		case MULTIPLY_OP:
			return leftOperand * rightOperand;
		case DIVIDE_OP:
			return leftOperand / rightOperand;
		case POWER_OP:
			return pow(leftOperand, rightOperand);
	}
}

long double evaluateConstantNode(ConstantNode* constantNode) {
	switch (constantNode->constantType) {
		case PI_NUMBER_CONSTANT:
			return M_PI;
		case EULER_NUMBER_CONSTANT:
			return M_E;
	}
	return 0L;
}

long double evaluateStdFunctionNode(StdFunctionNode* stdFunctionNode) {

}

long double evaluateBaseNode(BaseNode* baseNode) {
	switch (baseNode->nodeType) {
	case OPERATOR_NODE:
		return evaluateOperatorNode((OperatorNode*)baseNode->realNode);
	case NUMBER_NODE:
		return evaluateNumberNode((NumberNode*)baseNode->realNode);
	case CONSTANT_NODE:
		return evaluateConstantNode((ConstantNode*)baseNode->realNode);
	case STDFUNCTION_NODE:
		return evaluateStdFunctionNode((StdFunctionNode*)baseNode->realNode);
	}
	return 0L;
}