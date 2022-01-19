#ifndef NODE_HEADER
#define NODE_HEADER

// BASE NODE
enum NodeType {
    OPERATOR_NODE,       // ^; *; /; +; -; 
    NUMBER_NODE,         // 1; 1.2; -1.1; 0.012; 50; 24;
    CONSTANT_NODE,       // e; PI;
    STDFUNCTION_NODE,    // cos; sin; tg; log; ln; sqrt; pow; abs; exp; real; imag; mag; phase;
    VARIABLE_NODE        // alpha = sin(PI*2.5+sqrt(5)); beta = sqrt(sin(1)^2 <or> sqrt((sin(1))^2);
};
typedef enum NodeType NodeType;

typedef struct BaseNode BaseNode;
struct BaseNode {
    NodeType nodeType;
    void* realNode;
};

// OPERANDS CONTAINER
typedef struct OperandsContainer OperandsContainer;
struct OperandsContainer {
    BaseNode** operands;
    int operandsNumber;
};

// OPERATOR NODE
enum OperatorType {
    POWER_OP,
    MULTIPLY_OP,
    DIVIDE_OP,
    PLUS_OP,
    MINUS_OP
};
typedef enum OperatorType OperatorType;

typedef struct OperatorNode OperatorNode;
struct OperatorNode {
    OperatorType operatorType;
    OperandsContainer* operands;
};

// NUMBER NODE
typedef struct NumberNode NumberNode;
struct NumberNode {
    long double number;
};

// CONSTANT NODE
enum ConstantType {
    EULER_NUMBER_CONSTANT,   // e;
    PI_NUMBER_CONSTANT       // PI;
};
typedef enum ConstantType ConstantType;

typedef struct ConstantNode ConstantNode;
struct ConstantNode {
    ConstantType constantType;
};

// STD FUNCTION NODE
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

typedef struct StdFunctionNode StdFunctionNode;
struct StdFunctionNode {
    StdFunctionType stdFunctionType;
    OperandsContainer* operands;
};

// VARIABLE NODE
typedef struct VariableNode VariableNode;
struct VariableNode {
    char* variableName;
    OperandsContainer* operands;
};
#endif
