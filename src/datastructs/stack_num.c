#include "stack_num.h"

void init_stack_num(StackNum *stackNum) {
    for (int i = 0; i < STACK_MAX_SIZE; i++) {
        stackNum->numbers[i] = 0;
    }
    stackNum->size = 0;
}

void push_num(StackNum *stackNum, const double value) {
    stackNum->numbers[stackNum->size] = value;
    stackNum->size++;
}

double pop_num(StackNum *stackNum) {
    double result;
    result = stackNum->numbers[stackNum->size - 1];
    stackNum->numbers[stackNum->size - 1] = 0;
    stackNum->size--;
    return result;
}

// int is_empty_stack_num(StackNum *stackNum) {
//     int result = 0;
//     if (stackNum->size == 1) {
//         result = 1;
//     }
//     return result;
// }
