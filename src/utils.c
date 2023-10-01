#include "utils.h"

#include <ctype.h>
#include <stdbool.h>

void list_to_stack(Node *list, Stack *stack) {
    Stack tmpStack;
    init_stack(&tmpStack);
    while (list) {
        push(&tmpStack, *list);
        list = list->next;
    }
    while (is_empty(tmpStack) == 0) {
        push(stack, pop(&tmpStack));
    }
}

// -2*-5

double customAtof(const char *str) {
    double result = 0.0;
    double fraction = 1.0;
    int exponent = 0;
    bool negative = false;
    // bool fractionPart = false;
    bool exponentPart = false;

    // Пропустить начальные пробелы
    while (isspace(*str)) {
        str++;
    }

    // Обработка знака числа
    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Обработка целой части числа
    while (isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    // Обработка дробной части числа
    if (*str == '.') {
        // fractionPart = true;
        str++;
        while (isdigit(*str)) {
            fraction *= 0.1;
            result = result + (*str - '0') * fraction;
            str++;
        }
    }

    // Обработка экспоненты
    // if (*str == 'e' || *str == 'E') {
    //     exponentPart = true;
    //     str++;
    //     int expSign = 1;
    //     if (*str == '-') {
    //         expSign = -1;
    //         str++;
    //     } else if (*str == '+') {
    //         str++;
    //     }
    //     while (isdigit(*str)) {
    //         exponent = exponent * 10 + (*str - '0');
    //         str++;
    //     }
    //     exponent *= expSign;
    // }

    // Пропустить конечные пробелы
    while (isspace(*str)) {
        str++;
    }

    // Расчет окончательного результата
    result *= (negative ? -1 : 1);
    if (exponentPart) {
        result *= pow(10.0, (double)exponent);
    }

    return result;
}
