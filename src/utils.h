#ifndef UTILS_H
#define UTILS_H

#include <math.h>

#include "datastructs/linked_list.h"
#include "datastructs/stack_list.h"

void list_to_stack(Node *list, Stack *stack);
double customAtof(const char *str);
#endif  // UTILS_H