#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "datastructs/stack_list.h"
#include "datastructs/stack_num.h"
#include "parse_input.h"
#include "reverse_polish_notation.h"
#include "utils.h"

double computer2(char *exprsn_str, char *str_x);

double computer(char *str_exprs, double x);
void calc(Stack *stackToken, double *result, double x);
void token_processor(Node token, StackNum *stackNum, double x);
void num_handler(double num, StackNum *stackNum);
void symb_handler(char symb, StackNum *stackNum);
void cmnd_handler(Node token, StackNum *stackNum);
void unar_handler(Node token, StackNum *stackNum);
void x_handler(StackNum *stackNum, double x);

#endif  // CALCULATIONS_H