#include "parse_input.h"

#include <string.h>

int parse_input_str(char *str, Node **head) {
    int result_code = 0;

    while (*str != '\0' && result_code == 0) {
        if (check_unar(str, head)) {
        } else if (check_symb(str, head)) {
        } else if (check_num(&str, head)) {
        } else if (check_cmnd(&str, head)) {
        } else if (check_x(str, head)) {
        } else if (check_space(str)) {
        } else {
            result_code = 1;
        }
        str++;
    }
    return result_code;
}

int check_x(char *str, Node **head) {
    int is_x = 0;
    Data tmp_data;
    if (*str == 'x') {
        tmp_data.num = 0;
        add_node(head, tmp_data, X);
        is_x = 1;
    }
    return is_x;
}

int check_unar(char *str, Node **head) {
    int is_unar = 0;
    Data tmp_data;
    if (*str == '+' || *str == '-') {
        if (*head == NULL) {
            is_unar = 1;
        } else if (get_last(*head).dataType != NUM) {
            if (!(get_last(*head).dataType == SYMB &&
                  get_last(*head).data.symb == ')')) {
                if (get_last(*head).dataType != X) {
                    is_unar = 1;
                }
            }
        }
    }
    if (is_unar) {
        tmp_data.unar = *str;
        add_node(head, tmp_data, UNAR);
    }
    return is_unar;
}

int check_space(char *str) {
    int is_space = 0;
    if (*str == ' ') {
        is_space = 1;
    }
    return is_space;
}
int check_symb(char *str, Node **head) {
    int is_symb = 0;
    Data tmp_data;
    if (*str == '+' || *str == '-' || *str == '*' || *str == '/' ||
        *str == '(' || *str == ')' || *str == '^') {
        tmp_data.symb = *str;
        add_node(head, tmp_data, SYMB);
        is_symb = 1;
    }
    return is_symb;
}

int check_num(char **str, Node **head) {  // добавить валидацию
    int is_num = 0;
    Data tmp_data;
    // char *endptr = NULL;
    char num_str[STRMAX] = "!";
    int i = 0;
    while (((int)**str > 47 && (int)**str < 58) || **str == '.') {
        num_str[i] = **str;
        i++;
        *str = *str + 1;
    }
    if (i > 0) {
        tmp_data.num = 0;
        // tmp_data.num = strtod(num_str, &endptr);
        tmp_data.num = customAtof(num_str);

        add_node(head, tmp_data, NUM);
        *str = *str - 1;
        is_num = 1;
    }
    return is_num;
}

int check_cmnd(char **str, Node **head) {
    int result_code = 0;
    int is_cmnd = 0;
    char cmnd_str[CMNDMAX] = {'\0'};
    int i = 0;
    Data tmp_data;

    while ((int)*(*str + i) > 96 && (int)*(*str + i) < 123) {
        if (i >= CMNDMAX) {
            result_code = 1;
        } else {
            cmnd_str[i] = *(*str + i);
            i++;
        }
    }
    if (i > 0 && result_code == 0) {
        char valid[CMNDCOUNT][CMNDMAX] = {
            {"cos"},  {"sin"},  {"tan"}, {"acos"}, {"asin"},
            {"atan"}, {"sqrt"}, {"ln"},  {"log"},  {"mod"}};
        // validity check
        result_code = 1;
        for (int j = 0; j < CMNDCOUNT; j++) {
            if (strcmp(valid[j], cmnd_str) == 0) {
                memcpy(tmp_data.cmnd, cmnd_str, sizeof(cmnd_str));
                add_node(head, tmp_data, CMND);
                *str = *str + (i - 1);
                result_code = 0;
                break;
            }
        }
    }

    if (result_code == 0) {
        is_cmnd = 1;
    }
    return is_cmnd;
}

/*
cos(x)
sin(x)
tan(x)
acos(x)
asin(x)
atan(x)
sqrt(x)
ln(x)
log(x)
*/
