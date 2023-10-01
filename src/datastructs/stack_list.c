#include "stack_list.h"

void init_stack(Stack *stack) { stack->top = NULL; }

int is_empty(Stack stack) { return stack.top == NULL; }

void push(Stack *stack, Node dataNode) {
    Node *newNode = new_node(dataNode.data, dataNode.dataType);
    newNode->next = stack->top;
    stack->top = newNode;
}

Node pop(Stack *stack) {
    Node result = {};
    if (is_empty(*stack) == 0) {
        Node *tmp = stack->top;
        result = *tmp;
        stack->top = stack->top->next;
        free(tmp);
    }
    return result;
}
Node *peek(Stack stack) { return stack.top; }

// void print_stack(Stack stack) { print_list(stack.top); }
