
#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "linked_list.h"

typedef struct Stack {
    Node *top;
} Stack;

void init_stack(Stack *stack);
int is_empty(Stack stack);
void push(Stack *stack, Node dataNode);
Node pop(Stack *stack);
Node *peek(Stack stack);
void print_stack(Stack stack);

#endif  // STACK_LIST_H
