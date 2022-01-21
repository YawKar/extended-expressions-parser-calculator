#ifndef _STD_FUNCTION_TYPES_HEADER
#define _STD_FUNCTION_TYPES_HEADER

// StdFunctions (change in StdFunctionTypes)
extern char* globalStdFunctionsStrings[];
extern int globalStdFunctionsNumber;

enum StdFunctionType {
    COS_FUNC,
    SIN_FUNC,
    TG_FUNC,
    CTG_FUNC,
    LOG_FUNC,
    LN_FUNC,
    SQRT_FUNC,
    POW_FUNC,
    ABS_FUNC,
    EXP_FUNC,
    REAL_FUNC,
    IMAG_FUNC,
    MAG_FUNC,
    PHASE_FUNC
};
typedef enum StdFunctionType StdFunctionType;
#endif