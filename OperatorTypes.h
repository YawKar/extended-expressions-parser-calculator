#ifndef _OPERATOR_TYPES_HEADER
#define _OPERATOR_TYPES_HEADER

// Operators (change in OperatorTypes.c)
extern char* globalOperatorsCharacters;
extern int globalOperatorsNumber;

enum OperatorType {
    POWER_OP,
    MULTIPLY_OP,
    DIVIDE_OP,
    PLUS_OP,
    MINUS_OP
};
typedef enum OperatorType OperatorType;
#endif