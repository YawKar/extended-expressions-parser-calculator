#pragma once
#ifndef NODE_HEADER
#define NODE_HEADER

enum NodeType {
    Operator,       // ^; *; /; +; -; 
    Number,         // 1; 1.2; -1.1; 0.012; 50; 24;
    Constant,       // e; PI; j;
    StdFunction,    // cos; sin; tg; log; ln; sqrt; pow; abs; exp; real; imag; mag; phase;
    Variable,       // alpha = sin(PI*2.5+sqrt(5)); beta = sqrt(sin(1)^2 <or> sqrt((sin(1))^2);
    CustomFunction  // myFunc(a, b, c) = a*5+sin(b)+c;
};

typedef struct BaseNode BaseNode;
struct BaseNode {
    NodeType nodeType;
    void*
};

#endif
