#include "EvaluateNodesFunctions.h"
#define _USE_MATH_DEFINES
#include <math.h>

long double evaluateVariableNode(VariableNode* variableNode) {
	return evaluateBaseNode(variableNode->operands->operands[0]);
}

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

long double logWithBase(long double base, long double value) {
    return log(value) / log(base);
}

long double evaluateStdFunctionNode(StdFunctionNode* stdFunctionNode) {
	long double arg1 = 0L;
	long double arg2 = 0L;
	long double arg3 = 0L;
	switch (stdFunctionNode->stdFunctionType) {
		case COS_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return cos(arg1);
		case SIN_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return sin(arg1);
		case TG_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return tan(arg1);
		case CTG_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return cos(arg1) / sin(arg1);
		case LOG_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			arg2 = evaluateBaseNode(stdFunctionNode->operands->operands[1]);
			return logWithBase(arg1, arg2);
		case LN_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return log(arg1);
		case SQRT_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return sqrt(arg1);
		case POW_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			arg2 = evaluateBaseNode(stdFunctionNode->operands->operands[1]);
			return pow(arg1, arg2);
		case ABS_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return fabs(arg1);
		case EXP_FUNC:
			arg1 = evaluateBaseNode(stdFunctionNode->operands->operands[0]);
			return exp(arg1);
		case REAL_FUNC:
			return 0L;
		case IMAG_FUNC:
			return 0L;
		case MAG_FUNC:
			return 0L;
		case PHASE_FUNC:
			return 0L;
	}
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
	case VARIABLE_NODE:
		return evaluateVariableNode((VariableNode*)baseNode->realNode);
	}
	return 0L;
}