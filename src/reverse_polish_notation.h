#ifndef REVERSE_POLISH_NOTATION_H
#define REVERSE_POLISH_NOTATION_H

#include <math.h>

#include "datastructs/stack_list.h"

// infix notation -> postfix notation

void infix_to_postfix_notation(
    Node *listInfix,
    Node **listPostfix);  // На вход поступает уже выражение прошедшее валидацию
void token_handler(Node token, Node **listPostfix, Stack *stackTokens);
void num_solver(Node token, Node **listPostfix);
void symb_solver(Node token, Node **listPostfix, Stack *stackTokens);
void cmnd_solver(Node token, Stack *stackTokens);
void unar_solver(Node token, Stack *stackTokens);
int get_priority(Node token);
void x_solver(Node token, Node **listPostfix);
#endif  // REVERSE_POLISH_NOTATION_H