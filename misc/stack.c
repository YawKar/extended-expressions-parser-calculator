#include <stdlib.h>
#include "stack.h"

void free_stack (Stack* stack) {
    if (stack == NULL)
        return;
    if (stack->_stack != NULL)
        free(stack->_stack);
    stack->_stack = NULL;
    free(stack);
    stack = NULL;
}

int is_empty_stack (Stack* stack) {
    return stack->_length == 0;
}

int peek_stack (Stack* stack) {
    return stack->_stack[stack->_length - 1];
}

int pop_stack (Stack* stack) {
    int value = stack->_stack[stack->_length - 1];
    --stack->_length;
    return value;
}

void push_stack (Stack* stack, int value) {
    if (stack->_length < stack->_capacity) {
        stack->_stack[stack->_length] = value;
        ++stack->_length;
    } else {
        int* new_stack = (int*) malloc(sizeof(int) * (stack->_capacity * 2 + 1));
        for (int i = 0; i < stack->_length; ++i)
            new_stack[i] = stack->_stack[i];
        if (stack->_stack != NULL)
            free(stack->_stack);
        stack->_stack = new_stack;
        stack->_stack[stack->_length] = value;
        ++stack->_length;
    }
}
