#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "nodes.h"
#include "misc/string_procedures.h"
#include "misc/stack.h"

int is_forbidden_char (char ch) {
    char* forbid_chars = " \n\t\r\0";
    int forbid_len = strlen(forbid_chars);
    for (int i = 0; i < forbid_len; ++i)
        if (ch == forbid_chars[i])
            return 1;
    return ch == '\0';
}

int is_operator (char ch) {
    char* operators = "^*/+-\0";    
    int operators_len = strlen(operators);
    for (int i = 0; i < operators_len; ++i)
        if (operators[i] == ch)
            return 1;
    return 0;
}

char* prettify_expression (char* expression) {
    int exps_len = strlen(expression);
    int final_len = 0;
    for (int i = 0; i < exps_len; ++i) {
        if (!is_forbidden_char(expression[i]))
            ++final_len;
    }
    int cur_index = 0;
    char* prettified = (char*) malloc(sizeof(char) * (final_len + 1));
    for (int i = 0; i < exps_len; ++i) {
        if (!is_forbidden_char(expression[i]))
            prettified[cur_index++] = expression[i];
    }
    prettified[cur_index] = '\0';
    return prettified;
}

int is_bracketed (char* expression, int left, int right) {
    if (expression[left] != '(' || expression[right - 1] != ')')
        return 0;
    int min_level_operator = -1;
    int cur_level = 0;
    for (int i = left; i < right; ++i) {
        if (is_operator(expression[i])) {
            if (min_level_operator == -1)
                min_level_operator = cur_level;
            else if (min_level_operator > cur_level)
                min_level_operator = cur_level;
        } else if (expression[i] == '(') {
            ++cur_level;
        } else if (expression[i] == ')') {
            --cur_level;
        }
    }
    return min_level_operator != 0;
}

int count_ends_brackets (char* expression, int left, int right) {
    int ends_brackets = 0;
    while (right - left - 2 * ends_brackets > 1) {
        if (is_bracketed(expression, left + ends_brackets, right - ends_brackets))
            ++ends_brackets;
        else
            break;
    }
    return ends_brackets;
}

int has_operator (char* expression, int left, int right) {
    char* operators = "^*/+-\0";
    int operators_len = strlen(operators);
    int cur_level = 0;
    for (int i = left; i < right; ++i) {
        if (expression[i] == '(') {
            ++cur_level;
            continue;
        }
        if (expression[i] == ')') {
            --cur_level;
            continue;
        }
        if (cur_level != 0)
            continue;
        for (int j = 0; j < operators_len; ++j) {
            if (expression[i] == operators[j])
                return 1;
        }
    }
    return 0;
}

int get_max_operator_index (char* expression, int left, int right) {
    char* operators = "^*/+-\0";
    int operators_len = strlen(operators);
    int cur_level = 0;
    int max_operator_index = -1;
    int max_operator_order = -1;
    for (int i = left; i < right; ++i) {
        if (expression[i] == '(') {
            ++cur_level;
            continue;
        }
        if (expression[i] == ')') {
            --cur_level;
            continue;
        }
        if (cur_level != 0)
            continue;
        for (int j = 0; j < operators_len; ++j) {
            if (expression[i] == operators[j]) {
                if (j > max_operator_order) {
                    max_operator_order = j;
                    max_operator_index = i;
                }
            }
        }
    }
    return max_operator_index;
}

OperatorType get_operator_type (char operator) {
    switch (operator) {
        case '^':
            return POWER_OP;
        case '*':
            return MULTIPLY_OP;
        case '/':
            return DIVIDE_OP;
        case '+':
            return PLUS_OP;
        case '-':
            return MINUS_OP;
    }
    return PLUS_OP;
}

OperandsContainer* new_operands_container () {
    OperandsContainer* res = (OperandsContainer*) malloc(sizeof(OperandsContainer));
    res->operands = NULL;
    res->operandsNumber = 0;
    return res;
}

BaseNode* new_base_node () {
    BaseNode* res = (BaseNode*) malloc(sizeof(BaseNode));
    res->realNode = NULL;
    return res;
}

void add_operand_to_oper_node (OperatorNode* opNode, BaseNode* operand) {
    int prevOperandsCount = opNode->operands->operandsNumber;
    BaseNode** newOperands = (BaseNode**) malloc(sizeof(BaseNode*) * (prevOperandsCount + 1));
    for (int i = 0; i < prevOperandsCount; ++i) {
        newOperands[i] = opNode->operands->operands[i];
    }
    if (opNode->operands->operands != NULL)
        free(opNode->operands->operands);
    newOperands[prevOperandsCount] = operand;
    opNode->operands->operands = newOperands;
    ++opNode->operands->operandsNumber;
}

int is_number (char* expression, int left, int right) {
    int countDots = 0;
    int startIndex = left;
    while (expression[startIndex] == '-' || expression[startIndex] == '+')
        ++startIndex;
    for (int i = startIndex; i < right; ++i) {
        if (expression[i] == '.')
            ++countDots;
        else if (!(expression[i] >= '0' && expression[i] <= '9')) {
            return 0;
        }
    }
    return countDots < 2;
}

long double binpow (long double baseNum, long long powerNum) {
    if (powerNum == 0)
        return 1L;
    if (powerNum % 2 == 0) {
        long double half = binpow(baseNum, powerNum / 2LL);
        return half * half;
    } else {
        return baseNum * binpow(baseNum, powerNum - 1LL);
    }
}

long double parse_number (char* expression, int left, int right) {
    int sign = 0;
    int startIndex = left;
    while (expression[startIndex] == '-' || expression[startIndex] == '+') {
        sign ^= expression[startIndex] == '-';
        ++startIndex;
    }
    long double res = 0;
    int dotIndex = -1;
    for (int i = startIndex; i < right; ++i) {
        if (expression[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    if (dotIndex == -1)
        dotIndex = right;
    for (int i = startIndex; i < dotIndex; ++i) {
        res += binpow(10L, dotIndex - i - 1) * (long double) (expression[i] - '0');
    }
    for (int i = dotIndex + 1; i < right; ++i) {
        res += pow(10L, dotIndex - i) * (long double) (expression[i] - '0');
    }
    return res;
}

int is_constant (char* expression, int left, int right) {
    char* constants[] = {
        "PI\0", "e\0"
    };
    int constantsNumber = 2;
    for (int i = 0; i < constantsNumber; ++i) {
        int constLen = strlen(constants[i]);
        if (constLen != right - left)
            continue;
        int areEqual = 1;
        for (int j = 0; j < constLen; ++j) {
            areEqual &= constants[i][j] == expression[left + j];
        }
        if (areEqual)
            return 1;
    }
    return 0;
}

ConstantType get_constant_type (char* expression, int left, int right) {
    char* constants[] = {
        "PI\0", "e\0"
    };
    int constantsNumber = 2;
    for (int i = 0; i < constantsNumber; ++i) {
        int constLen = strlen(constants[i]);
        if (constLen != right - left)
            continue;
        int areEqual = 1;
        for (int j = 0; j < constLen; ++j) {
            areEqual &= constants[i][j] == expression[left + j];
        }
        if (areEqual) {
            switch (i) {
                case 0:
                    return PI_NUMBER_CONSTANT;
                case 1:
                    return EULER_NUMBER_CONSTANT;
            }
        }
    }
    return PI_NUMBER_CONSTANT;
}

int is_stdfunction(char* expression, int left, int right) {
    char* stdFunctions[] = {
        "cos\0",
        "sin\0",
        "tg\0",
        "ctg\0",
        "log\0",
        "ln\0",
        "sqrt\0",
        "pow\0",
        "abs\0",
        "exp\0",
        "real\0",
        "imag\0",
        "mag\0",
        "phase\0"
    };
    int openBracketIndex = -1;
    for (int i = left; i < right; ++i) {
        if (expression[i] == '(') {
            openBracketIndex = i;
            break;
        }
    }
    if (openBracketIndex == -1)
        return 0;
    int stdFuncNumber = 14;
    for (int funcIndex = 0; funcIndex < stdFuncNumber; ++funcIndex) {
        int stdFuncLen = strlen(stdFunctions[funcIndex]);
        if (stdFuncLen != openBracketIndex - left)
            continue;
        int areEqual = 1;
        for (int j = 0; j < stdFuncLen; ++j)
            if (stdFunctions[funcIndex][j] != expression[left + j]) {
                areEqual = 0;
                break;
            }
        if (areEqual) {
            return 1;
        }
    }
    return 0;
}

StdFunctionType get_stdfunc_type(char* expression, int left, int right) {
    char* stdFunctions[] = {
        "cos\0",
        "sin\0",
        "tg\0",
        "ctg\0",
        "log\0",
        "ln\0",
        "sqrt\0",
        "pow\0",
        "abs\0",
        "exp\0",
        "real\0",
        "imag\0",
        "mag\0",
        "phase\0"
    };
    int openBracketIndex = -1;
    for (int i = left; i < right; ++i) {
        if (expression[i] == '(') {
            openBracketIndex = i;
            break;
        }
    }
    int stdFuncNumber = 14;
    for (int funcIndex = 0; funcIndex < stdFuncNumber; ++funcIndex) {
        int stdFuncLen = strlen(stdFunctions[funcIndex]);
        if (stdFuncLen != openBracketIndex - left)
            continue;
        int areEqual = 1;
        for (int j = 0; j < stdFuncLen; ++j)
            if (stdFunctions[funcIndex][j] != expression[left + j]) {
                areEqual = 0;
                break;
            }
        if (areEqual) {
            switch (funcIndex) {
                case 0:
                    return COS_FUNC;
                case 1:
                    return SIN_FUNC;
                case 2:
                    return TG_FUNC;
                case 3:
                    return CTG_FUNC;
                case 4:
                    return LOG_FUNC;
                case 5:
                    return LN_FUNC;
                case 6:
                    return SQRT_FUNC;
                case 7:
                    return POW_FUNC;
                case 8:
                    return ABS_FUNC;
                case 9:
                    return EXP_FUNC;
                case 10:
                    return REAL_FUNC;
                case 11:
                    return IMAG_FUNC;
                case 12:
                    return MAG_FUNC;
                case 13:
                    return PHASE_FUNC;
            }
        }
    }
    return COS_FUNC;
}

void add_operand_to_operands_container(BaseNode* operand, OperandsContainer* opContainer) {
    BaseNode** newOperands = (BaseNode**) malloc(sizeof(BaseNode*) * (opContainer->operandsNumber + 1));
    for (int i = 0; i < opContainer->operandsNumber; ++i) {
        newOperands[i] = opContainer->operands[i];
    }
    newOperands[opContainer->operandsNumber] = operand;
    free(opContainer->operands);
    opContainer->operands = newOperands;
    ++opContainer->operandsNumber;
}

void parse_expression (BaseNode* root, char* expression, int left, int right);

void parse_arguments (char* expression, int left, int right, OperandsContainer* operands) {
    int openBracketIndex = -1;
    for (int i = left; i < right; ++i) {
        if (expression[i] == '(') {
            openBracketIndex = i;
            break;
        }
    }
    int lastComma = openBracketIndex;
    int curLevel = 0;
    for (int i = openBracketIndex + 1; i < right - 1; ++i) {
        if (expression[i] == '(') {
            ++curLevel;
            continue;
        }
        if (expression[i] == ')') {
            --curLevel;
            continue;
        }
        if (curLevel != 0)
            continue;
        if (expression[i] == ',') {
            // FOUND ARGUMENT
            BaseNode* newOperand = new_base_node();
            add_operand_to_operands_container(newOperand, operands);
            parse_expression(newOperand, expression, lastComma + 1, i);
            lastComma = i;
        }
    }
    // LAST ARGUMENT
    BaseNode* newOperand = new_base_node();
    add_operand_to_operands_container(newOperand, operands);
    parse_expression(newOperand, expression, lastComma + 1, right - 1);
}

char* get_var_name (char* expression, int left, int right) {
    char* var_name = (char*) malloc(sizeof(char) * (right - left + 1));
    for (int i = left; i < right; ++i) {
        var_name[i - left] = expression[i];
    }
    var_name[right - left] = '\0';
    return var_name;
}

void parse_expression (BaseNode* root, char* expression, int left, int right) {
    if (is_bracketed(expression, left, right)) {
        int brackets_count = count_ends_brackets(expression, left, right);
        left += brackets_count;
        right -= brackets_count;
    }
    if (has_operator(expression, left, right)) {
        // At least two sub-expressions
        int max_operator_index = get_max_operator_index(expression, left, right);
        OperatorType max_oper = get_operator_type(expression[max_operator_index]);
        root->nodeType = OPERATOR_NODE;
        switch (max_oper) {
            case POWER_OP:
                {
                    OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                    opNode->operatorType = POWER_OP;
                    opNode->operands = new_operands_container();
                    root->realNode = (void*) opNode;
                }
                break;
            case MULTIPLY_OP:
                {
                    OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                    opNode->operatorType = MULTIPLY_OP;  
                    opNode->operands = new_operands_container();
                    root->realNode = (void*) opNode;
                }
                break;
            case DIVIDE_OP:
                {
                    OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                    opNode->operatorType = DIVIDE_OP;  
                    opNode->operands = new_operands_container();
                    root->realNode = (void*) opNode;
                }
                break;
            case PLUS_OP:
                {
                    OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                    opNode->operatorType = PLUS_OP;  
                    opNode->operands = new_operands_container();
                    root->realNode = (void*) opNode;
                }
                break;
            case MINUS_OP:
                {
                    OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                    opNode->operatorType = MINUS_OP;  
                    opNode->operands = new_operands_container();
                    root->realNode = (void*) opNode;
                }
                break;
        }
        OperatorNode* opNode = (OperatorNode*) root->realNode;
        BaseNode* leftOperand = new_base_node();
        BaseNode* rightOperand = new_base_node();
        add_operand_to_operands_container(leftOperand, opNode->operands);
        add_operand_to_operands_container(rightOperand, opNode->operands);
        parse_expression(leftOperand, expression, left, max_operator_index);
        parse_expression(rightOperand, expression, max_operator_index + 1, right);
    } else if (is_number(expression, left, right)) {
        // A number: 1.2; -1.4; 53;
        long double number = parse_number(expression, left, right);
        root->nodeType = NUMBER_NODE;
        NumberNode* numNode = (NumberNode*) malloc(sizeof(NumberNode));
        numNode->number = number;
        root->realNode = (void*) numNode;
    } else if (is_constant(expression, left, right)) {
        // A constant: e, PI;
        ConstantNode* consNode = (ConstantNode*) malloc(sizeof(ConstantNode));
        consNode->constantType = get_constant_type(expression, left, right);
        root->nodeType = CONSTANT_NODE;
        root->realNode = (void*) consNode;
    } else if (is_stdfunction(expression, left, right)) {
        // A std function: cos, sin...
        StdFunctionNode* stdFuncNode = (StdFunctionNode*) malloc(sizeof(StdFunctionNode));
        stdFuncNode->stdFunctionType = get_stdfunc_type(expression, left, right);
        stdFuncNode->operands = new_operands_container();
        root->nodeType = STDFUNCTION_NODE;
        root->realNode = (void*) stdFuncNode;
        parse_arguments(expression, left, right, stdFuncNode->operands);
    } else {
        // A variable;
        root->nodeType = VARIABLE_NODE;
        char* variableName = get_var_name(expression, left, right);
        if (isVariableInTable(varsTable, variableName)) {
            // Already exists
            root->realNode = (void*) get_variable_node_by_name(varsTable, variableName);
        } else {
            // Doesn't exist
            VariableNode* varNode = (VariableNode*) malloc(sizeof(VariableNode));
            varNode->variableName = variableName;
            varNode->operands = new_operands_container();
            root->realNode = (void*) varNode;
            addVariableToTable(varsTable, varNode);
        }
    }
}

long double eval_base_node (BaseNode* root);

long double eval_operator_node (OperatorNode* opNode) {
    long double arg1;
    long double arg2;
    switch (opNode->operatorType) {
        case POWER_OP:
            arg1 = eval_base_node(opNode->operands->operands[0]);
            arg2 = eval_base_node(opNode->operands->operands[1]);
            return pow(arg1, arg2);
        case MULTIPLY_OP:
            arg1 = eval_base_node(opNode->operands->operands[0]);
            arg2 = eval_base_node(opNode->operands->operands[1]);
            return arg1 * arg2;
        case DIVIDE_OP:
            arg1 = eval_base_node(opNode->operands->operands[0]);
            arg2 = eval_base_node(opNode->operands->operands[1]);
            return arg1 / arg2;
        case PLUS_OP:
            arg1 = eval_base_node(opNode->operands->operands[0]);
            arg2 = eval_base_node(opNode->operands->operands[1]);
            return arg1 + arg2;
        case MINUS_OP:
            arg1 = eval_base_node(opNode->operands->operands[0]);
            arg2 = eval_base_node(opNode->operands->operands[1]);
            return arg1 - arg2;
    }
    return 0L;
}

long double eval_number_node (NumberNode* numNode) {
    return numNode->number;
}

long double eval_constant_node (ConstantNode* consNode) {
    switch (consNode->constantType) {
        case EULER_NUMBER_CONSTANT:
            return exp(1.0);
        case PI_NUMBER_CONSTANT:
            return M_PI;
    }
    return 0L;
}

long double logWithBase (long double base, long double value) {
    return log(value) / log(base);
}

long double eval_stdfunction_node (StdFunctionNode* stdFunctionNode) {
    long double arg1;
    long double arg2;
    switch (stdFunctionNode->stdFunctionType) {
        case COS_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return cos(arg1);
        case SIN_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return sin(arg1);
        case TG_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return tan(arg1);
        case CTG_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return cos(arg1) / sin(arg1);
        case LOG_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            arg2 = eval_base_node(stdFunctionNode->operands->operands[1]);
            return logWithBase(arg1, arg2);
        case LN_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return log(arg1);
        case SQRT_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return sqrt(arg1);
        case POW_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            arg2 = eval_base_node(stdFunctionNode->operands->operands[1]);
            return pow(arg1, arg2);
        case ABS_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
            return fabs(arg1);
        case EXP_FUNC:
            arg1 = eval_base_node(stdFunctionNode->operands->operands[0]);
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
    return 0L;
}

long double eval_base_node (BaseNode* root) {
    switch (root->nodeType) {
        case OPERATOR_NODE:
            return eval_operator_node((OperatorNode*)root->realNode);
        case NUMBER_NODE:
            return eval_number_node((NumberNode*)root->realNode);
        case CONSTANT_NODE:
            return eval_constant_node((ConstantNode*)root->realNode);
        case STDFUNCTION_NODE:
            return eval_stdfunction_node((StdFunctionNode*)root->realNode);
    }
    return 0;
}

int main () {
    char* raw_expression = get_line();
    char* expression = prettify_expression(raw_expression);
    int expression_length = strlen(expression);
    BaseNode* root = new_base_node();
    parse_expression(root, expression, 0, expression_length);
    printf("Evaluate: %Lf", eval_base_node(root));
    return 0;
}
