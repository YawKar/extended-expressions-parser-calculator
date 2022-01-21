#ifndef _CONSTANT_TYPES_HEADER
#define _CONSTANT_TYPES_HEADER

// Constants (change in ConstantTypes.c)
extern char* globalConstantsStrings[];
extern int globalConstantsNumber;

enum ConstantType {
    PI_NUMBER_CONSTANT,
    EULER_NUMBER_CONSTANT
};
typedef enum ConstantType ConstantType;
#endif