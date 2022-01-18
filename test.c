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
    int max_operator_order = 1000;
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
                if (j < max_operator_order) {
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
                OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                opNode->operatorType = POWER_OP;
                opNode->operands = new_operands_container();
                root->realNode = (void*) opNode;
                break;
            case MULTIPLY_OP:
                OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                opNode->operatorType = MULTIPLY_OP;  
                opNode->operands = new_operands_container();
                root->realNode = (void*) opNode;
                break;
            case DIVIDE_OP:
                OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                opNode->operatorType = DIVIDE_OP;  
                opNode->operands = new_operands_container();
                root->realNode = (void*) opNode;
                break;
            case PLUS_OP:
                OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                opNode->operatorType = PLUS_OP;  
                opNode->operands = new_operands_container();
                root->realNode = (void*) opNode;
                break;
            case MINUS_OP:
                OperatorNode* opNode = (OperatorNode*) malloc(sizeof(OperatorNode));
                opNode->operatorType = MINUS_OP;  
                opNode->operands = new_operands_container();
                root->realNode = (void*) opNode;
                break;
        }
        OperatorNode* opNode = (OperatorNode*) root->realNode;
        BaseNode* leftOperand = new_base_node();
        BaseNode* rightOperand = new_base_node();
        add_operand_to_oper_node(opNode, leftOperand);
        add_operand_to_oper_node(opNode, rightOperand);
        parse_expression(leftOperand, expression, left, max_operator_index);
        parse_expression(rightOperand, expression, max_operator_index + 1, right);
    } else if (is_number(expression, left, right)) {
        // A number: 1.2; -1.4; 53;
        long double number = parse_number(expression, left, right);
        root->nodeType = NUMBER_NODE;
        NumberNode* numNode = (NumberNode*) malloc(sizeof(NumberNode));
        numNode->number = number;
        root->realNode = (void*) numNode;
    }
}

int main () {
    char* raw_expression = get_line();
    char* expression = prettify_expression(raw_expression);
    int expression_length = strlen(expression);
    BaseNode* root = (BaseNode*) malloc(sizeof(BaseNode));
    parse_expression(root, expression, 0, expression_length);
    return 0;
}
