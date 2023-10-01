#include "calculations.h"

/*
Алгоритм:
1) Если число - помещается в стек
2) Если оператор - достается последние два выражения из стека и вычисляются
результат кладется обратно в стек


*/

double computer2(char *exprsn_str, char *str_x) {
    if (*exprsn_str == '=') {
        exprsn_str = exprsn_str + 1;
    }
    // char **endptr = NULL;
    // double x = strtod(str_x, endptr);
    double x = customAtof(str_x);
    double result;
    result = computer(exprsn_str, x);
    return result;
}

double computer(char *exprsn_str, double x) {
    double result;
    Node *infixStr = NULL;
    Node *postfixStr = NULL;
    Stack stackToken;

    init_stack(&stackToken);
    parse_input_str(exprsn_str, &infixStr);
    // print_list(infixStr);

    infix_to_postfix_notation(infixStr, &postfixStr);
    // print_list(postfixStr);

    list_to_stack(postfixStr, &stackToken);
    // print_stack(stackToken);

    calc(&stackToken, &result, x);

    destroy(infixStr);
    destroy(postfixStr);

    return result;
}

void calc(Stack *stackToken, double *result, double x) {
    StackNum stackNum;
    init_stack_num(&stackNum);

    while (is_empty(*stackToken) == 0) {
        token_processor(pop(stackToken), &stackNum, x);
    }
    *result = pop_num(&stackNum);
}

void token_processor(Node token, StackNum *stackNum, double x) {
    switch (token.dataType) {
        case NUM:
            num_handler(token.data.num, stackNum);
            break;
        case SYMB:
            symb_handler(token.data.symb, stackNum);
            break;
        case CMND:
            cmnd_handler(token, stackNum);
            break;
        case UNAR:
            unar_handler(token, stackNum);
            break;
        case X:
            x_handler(stackNum, x);
            break;
        default:
            break;
    }
}
void x_handler(StackNum *stackNum, double x) { push_num(stackNum, x); }

void unar_handler(Node token, StackNum *stackNum) {
    if (token.data.unar == '-') {
        double num;
        num = pop_num(stackNum);
        push_num(stackNum, -num);
    }
}

void cmnd_handler(Node token, StackNum *stackNum) {
    double num;
    num = pop_num(stackNum);
    if (strcmp(token.data.cmnd, "cos") == 0) {
        push_num(stackNum, cos(num));
    } else if (strcmp(token.data.cmnd, "sin") == 0) {
        push_num(stackNum, sin(num));
    } else if (strcmp(token.data.cmnd, "tan") == 0) {
        push_num(stackNum, tan(num));
    } else if (strcmp(token.data.cmnd, "acos") == 0) {
        push_num(stackNum, acos(num));
    } else if (strcmp(token.data.cmnd, "asin") == 0) {
        push_num(stackNum, asin(num));
    } else if (strcmp(token.data.cmnd, "atan") == 0) {
        push_num(stackNum, atan(num));
    } else if (strcmp(token.data.cmnd, "sqrt") == 0) {
        push_num(stackNum, sqrt(num));
    } else if (strcmp(token.data.cmnd, "ln") == 0) {
        push_num(stackNum, log(num));
    } else if (strcmp(token.data.cmnd, "log") == 0) {
        push_num(stackNum, log10(num));
    } else if (strcmp(token.data.cmnd, "mod") == 0) {
        long int num2 = (long int)pop_num(stackNum);
        long int num1 = (long int)num;
        push_num(stackNum, (num2 % num1));
    }
}
void num_handler(double num, StackNum *stackNum) { push_num(stackNum, num); }

void symb_handler(char symb, StackNum *stackNum) {
    double num_1;
    double num_2;

    num_1 = pop_num(stackNum);
    num_2 = pop_num(stackNum);

    switch (symb) {
        case '+':
            push_num(stackNum, (num_1 + num_2));
            break;
        case '-':
            push_num(stackNum, (num_2 - num_1));
            break;
        case '*':
            push_num(stackNum, (num_1 * num_2));
            break;
        case '/':
            push_num(stackNum, (num_2 / num_1));
            break;
        case '^':
            push_num(stackNum, pow(num_2, num_1));
            break;
        default:
            break;
    }
}
