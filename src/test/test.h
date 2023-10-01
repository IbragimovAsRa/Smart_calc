#ifndef TEST_GENERAL_H_
#define TEST_GENERAL_H_

#include <check.h>
#include <stdio.h>

#include "../calculations.h"
#include "../parse_input.h"
#include "../reverse_polish_notation.h"

#define accuracy 1e-6

Suite *get_suite_general();

#endif  //  TEST_GENERAL_H_