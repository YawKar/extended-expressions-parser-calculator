#ifndef STACK_REALISATION
#define STACK_REALISATION
typedef struct Stack Stack;
struct Stack {
    int _capacity;
    int _length;
    int* _stack;
};

void free_stack (Stack* stack);

int is_empty_stack (Stack* stack);

int peek_stack (Stack* stack);

int pop_stack (Stack* stack);

void push_stack (Stack* stack, int value);
#endif
