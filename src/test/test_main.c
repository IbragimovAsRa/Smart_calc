#include "test.h"

void test_func_calc(Suite *s);

int main(void) {
    Suite *general_test_cases[20];

    general_test_cases[0] = get_suite_general();
    printf("START TEST general\n");
    test_func_calc(general_test_cases[0]);

    return 0;
}

void test_func_calc(Suite *s) {
    SRunner *runner = srunner_create(s);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);
}
