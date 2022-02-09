#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ExpressionFunctions.h"
#include "../EnumTypes/OperatorTypes.h"
#include "../EnumTypes/ConstantTypes.h"
#include "../EnumTypes/StdFunctionTypes.h"

StdFunctionType getStdFunctionType(char* expression, int leftBorder, int rightBorder) {
    int openBracketIndex = -1;
    for (int i = leftBorder; i < rightBorder; ++i) {
        if (expression[i] == '(') {
            openBracketIndex = i;
            break;
        }
    }
    if (openBracketIndex == -1)
        return 0;
    for (int stdFunctionIndex = 0; stdFunctionIndex < globalStdFunctionsNumber; ++stdFunctionIndex) {
        int stdFunctionLen = strlen(globalStdFunctionsStrings[stdFunctionIndex]);
        if (stdFunctionLen != openBracketIndex - leftBorder)
            continue;
        int areEqual = 1;
        for (int j = 0; j < stdFunctionLen; ++j)
            if (globalStdFunctionsStrings[stdFunctionIndex][j] != expression[leftBorder + j]) {
                areEqual = 0;
                break;
            }
        if (areEqual) {
            return (StdFunctionType)stdFunctionIndex;
        }
    }
    return SIN_FUNC;
}

int doesExpressionContainStdFunctionOnTop(char* expression, int leftBorder, int rightBorder) {
    int openBracketIndex = -1;
    for (int i = leftBorder; i < rightBorder; ++i) {
        if (expression[i] == '(') {
            openBracketIndex = i;
            break;
        }
    }
    if (openBracketIndex == -1)
        return 0;
    for (int stdFunctionIndex = 0; stdFunctionIndex < globalStdFunctionsNumber; ++stdFunctionIndex) {
        int stdFunctionLen = strlen(globalStdFunctionsStrings[stdFunctionIndex]);
        if (stdFunctionLen != openBracketIndex - leftBorder)
            continue;
        int areEqual = 1;
        for (int j = 0; j < stdFunctionLen; ++j)
            if (globalStdFunctionsStrings[stdFunctionIndex][j] != expression[leftBorder + j]) {
                areEqual = 0;
                break;
            }
        if (areEqual) {
            return 1;
        }
    }
    return 0;
}

ConstantType getConstantType(char* expression, int leftBorder, int rightBorder) {
    for (int constantIndex = 0; constantIndex < globalConstantsNumber; ++constantIndex) {
        int constantLen = strlen(globalConstantsStrings[constantIndex]);
        if (constantLen != rightBorder - leftBorder)
            continue;
        int areEqual = 1;
        for (int j = 0; j < constantLen; ++j) {
            areEqual &= globalConstantsStrings[constantIndex][j] == expression[leftBorder + j];
        }
        if (areEqual) {
            return (ConstantType)constantIndex;
        }
    }
    return PI_NUMBER_CONSTANT;
}

int doesExpressionContainConstantOnTop(char* expression, int leftBorder, int rightBorder) {
    for (int constantIndex = 0; constantIndex < globalConstantsNumber; ++constantIndex) {
        int constantLen = strlen(globalConstantsStrings[constantIndex]);
        if (constantLen != rightBorder - leftBorder)
            continue;
        int areEqual = 1;
        for (int i = 0; i < constantLen; ++i) {
            areEqual &= globalConstantsStrings[constantIndex][i] == expression[leftBorder + i];
        }
        if (areEqual)
            return 1;
    }
    return 0;
}

long double parseNumber(char* expression, int leftBorder, int rightBorder) {
    int numberSign = 0;
    int startIndex = leftBorder;
    while (expression[startIndex] == '-' || expression[startIndex] == '+') {
        numberSign ^= expression[startIndex] == '-';
        ++startIndex;
    }
    long double parsedNumber = 0;
    int dotIndex = -1;
    for (int i = startIndex; i < rightBorder; ++i) {
        if (expression[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    if (dotIndex == -1)
        dotIndex = rightBorder;
    for (int i = startIndex; i < dotIndex; ++i) {
        parsedNumber += pow(10L, (long double)dotIndex - i - 1) * ((long double)expression[i] - '0');
    }
    for (int i = dotIndex + 1; i < rightBorder; ++i) {
        parsedNumber += pow(10L, (long double)dotIndex - i) * ((long double)expression[i] - '0');
    }
    if (numberSign == 1)
        parsedNumber *= -1.0L;
    return parsedNumber;
}

int doesExpressionContainNumberOnTop(char* expression, int leftBorder, int rightBorder) {
    int countDots = 0;
    int startIndex = leftBorder;
    while (expression[startIndex] == '-' || expression[startIndex] == '+')
        ++startIndex;
    for (int i = startIndex; i < rightBorder; ++i) {
        if (expression[i] == '.')
            ++countDots;
        else if (!(expression[i] >= '0' && expression[i] <= '9')) {
            return 0;
        }
    }
    return countDots < 2;
}

OperatorType getOperatorType(char ch) {
    for (int operatorIndex = 0; operatorIndex < globalOperatorsNumber; ++operatorIndex) {
        if (globalOperatorsCharacters[operatorIndex] == ch) {
            return (OperatorType)operatorIndex;
        }
    }
    return PLUS_OP;
}

int getHighestOperatorIndex(char* expression, int leftBorder, int rightBorder) {
    int currentLevel = 0;
    int highestOperatorIndex = -1;
    int highestOperator = -1;
    for (int i = leftBorder; i < rightBorder; ++i) {
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
        for (int j = 0; j < globalOperatorsNumber; ++j) {
            if (expression[i] == globalOperatorsCharacters[j]) {
                if (j > highestOperator) {
                    highestOperator = j;
                    highestOperatorIndex = i;
                }
            }
        }
    }
    return highestOperatorIndex;
}

int doesExpressionHaveOperatorOnTop(char* expression, int leftBorder, int rightBorder) {
    int currentLevel = 0;
    for (int i = leftBorder; i < rightBorder; ++i) {
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
        for (int j = 0; j < globalOperatorsNumber; ++j) {
            if (expression[i] == globalOperatorsCharacters[j])
                return 1;
        }
    }
    return 0;
}

int countEndsBrackets(char* expression, int leftBorder, int rightBorder) {
    int endsBracketsCounter = 0;
    while (rightBorder - leftBorder - 2 * endsBracketsCounter > 1) {
        if (isExpressionBracketed(expression, leftBorder + endsBracketsCounter, rightBorder - endsBracketsCounter))
            ++endsBracketsCounter;
        else
            break;
    }
    return endsBracketsCounter;
}

int isOperator(char ch) {
    for (int operatorIndex = 0; operatorIndex < globalOperatorsNumber; ++operatorIndex) {
        if (globalOperatorsCharacters[operatorIndex] == ch)
            return 1;
    }
    return 0;
}

int isExpressionBracketed(char* expression, int leftBorder, int rightBorder) {
    if (expression[leftBorder] != '(' || expression[rightBorder - 1] != ')')
        return 0;
    int minLevelWithOperator = -1;
    int currentLevel = 0;
    for (int i = leftBorder; i < rightBorder; ++i) {
        if (isOperator(expression[i])) {
            if (minLevelWithOperator == -1)
                minLevelWithOperator = currentLevel;
            else if (minLevelWithOperator > currentLevel)
                minLevelWithOperator = currentLevel;
        }
        else if (expression[i] == '(') {
            ++currentLevel;
        }
        else if (expression[i] == ')') {
            --currentLevel;
        }
    }
    return minLevelWithOperator != 0;
}

int isForbiddenCharacter(char ch) {
    char* forbiddenChars = " \n\t\r\0";
    int forbiddenCharsLen = strlen(forbiddenChars);
    for (int i = 0; i < forbiddenCharsLen; ++i)
        if (ch == forbiddenChars[i])
            return 1;
    return ch == '\0';
}

char* prettifyExpressionCopy(char* expression) {
    int expressionLength = strlen(expression);
    int prettifiedLength = 0;
    for (int i = 0; i < expressionLength; ++i) {
        if (!isForbiddenCharacter(expression[i]))
            ++prettifiedLength;
    }
    int currentPrettifiedIndex = 0;
    char* prettifiedExpression = (char*)malloc(sizeof(char) * (prettifiedLength + 1));
    for (int i = 0; i < expressionLength; ++i) {
        if (!isForbiddenCharacter(expression[i]))
            prettifiedExpression[currentPrettifiedIndex++] = expression[i];
    }
    prettifiedExpression[currentPrettifiedIndex] = '\0';
    return prettifiedExpression;
}
