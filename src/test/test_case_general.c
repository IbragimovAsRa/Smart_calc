#include "test.h"

START_TEST(test_1) {
    char *exprsn_str = "2+2-4";
    char *str_x = "0";
    double answer = 0;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_2) {
    char *exprsn_str = "2*(1+2)";
    char *str_x = "0";
    double answer = 6;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_3) {
    char *exprsn_str = "(2+2*5)-12";
    char *str_x = "0";
    double answer = 0;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_4) {
    char *exprsn_str = "(2+2*5)-12*x";
    char *str_x = "2";
    double answer = -12;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_5) {
    char *exprsn_str = "2+x*2";
    char *str_x = "2";
    double answer = 6;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_6) {
    char *exprsn_str = "x^2";
    char *str_x = "2";
    double answer = 4;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_7) {
    char *exprsn_str = "12-(x^2+1)";
    char *str_x = "2";
    double answer = 7;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_8) {
    char *exprsn_str = "cos(x)";
    char *str_x = "2.2";
    double answer = -0.58850111725;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_9) {
    char *exprsn_str = "sqrt(-x)";
    char *str_x = "-4";
    double answer = 2;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

START_TEST(test_10) {
    char *exprsn_str = "5 mod x";
    char *str_x = "2";
    double answer = 1;
    ck_assert_ldouble_eq_tol(computer2(exprsn_str, str_x), answer, accuracy);
}
END_TEST

Suite *get_suite_general() {
    Suite *s = suite_create("test suite ");
    TCase *tc = tcase_create("test cases");
    suite_add_tcase(s, tc);

    tcase_add_test(tc, test_1);
    tcase_add_test(tc, test_2);
    tcase_add_test(tc, test_3);
    tcase_add_test(tc, test_4);
    tcase_add_test(tc, test_5);
    tcase_add_test(tc, test_6);
    tcase_add_test(tc, test_7);
    tcase_add_test(tc, test_8);
    tcase_add_test(tc, test_9);
    tcase_add_test(tc, test_10);
    return s;
}
