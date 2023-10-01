#ifndef STACK_NUM_H
#define STACK_NUM_H

#define STACK_MAX_SIZE 50

#include <stdio.h>

typedef struct StackNum {
    double numbers[STACK_MAX_SIZE];
    size_t size;
} StackNum;

void init_stack_num(StackNum *stackNum);
void push_num(StackNum *stackNum, const double value);
double pop_num(StackNum *stackNum);
// int is_empty_stack_num(StackNum *stackNum);

#endif  // STACK_NUM_H
