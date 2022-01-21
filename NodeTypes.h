#ifndef _NODE_TYPES_HEADER
#define _NODE_TYPES_HEADER
enum NodeType {
    OPERATOR_NODE,       // ^; *; /; +; -; 
    NUMBER_NODE,         // 1; 1.2; -1.1; 0.012; 50; 24;
    CONSTANT_NODE,       // e; PI;
    STDFUNCTION_NODE,    // cos; sin; tg; log; ln; sqrt; pow; abs; exp; real; imag; mag; phase;
    VARIABLE_NODE,        // alpha = sin(PI*2.5+sqrt(5)); beta = sqrt(sin(1)^2 <or> sqrt((sin(1))^2);
    NULL_NODE
};
typedef enum NodeType NodeType;
#endif