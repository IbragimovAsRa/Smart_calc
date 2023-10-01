#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#define CMNDCOUNT 10

#include <math.h>

#include "datastructs/linked_list.h"
#include "utils.h"

// input str -> structured linked list (должна осуществляться валидация входной
// строки)

int parse_input_str(char *str, Node **head);
int check_unar(char *str, Node **head);
int check_symb(char *str, Node **head);
int check_num(char **str, Node **head);
int check_cmnd(char **str, Node **head);
int check_space(char *str);
int check_x(char *str, Node **head);

/*
1- не обработал
2- он его обработал
3- ошибка обработки

*/

#endif  // PARSE_INPUT_H