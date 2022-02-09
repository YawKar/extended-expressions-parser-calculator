#ifndef _NUMBER_NODE_HEADER
#define _NUMBER_NODE_HEADER
typedef struct NumberNode NumberNode;
struct NumberNode {
    long double number;
};

NumberNode* newNumberNode();
#endif