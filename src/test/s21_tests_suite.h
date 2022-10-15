#ifndef SRC_TEST_S21_TESTS_SUITE_H_
#define SRC_TEST_S21_TESTS_SUITE_H_

#include "../s21_decimal.h"

#include <check.h>
#include <stdio.h>

Suite *s21_add_suite(void);
Suite *s21_div_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_mod_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_decimal_to_float_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_less_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_not_equal_suite(void);
Suite *s21_floor_suite(void);
Suite *s21_round_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_negate_suite(void);

void s21_num2decimal(void);

#define SUITE_FUNCS                                                            \
  (Suite * (*[])(void)) {                                                      \
    s21_add_suite, s21_mul_suite, s21_sub_suite, s21_div_suite, s21_mod_suite, \
        s21_from_decimal_to_float_suite, s21_from_decimal_to_int_suite,        \
        s21_from_float_to_decimal_suite, s21_from_int_to_decimal_suite,        \
        s21_truncate_suite, s21_negate_suite, s21_floor_suite,                 \
        s21_round_suite, s21_is_greater_suite, s21_is_equal_suite,             \
        s21_is_greater_or_equal_suite, s21_is_less_suite,                      \
        s21_is_less_or_equal_suite, s21_is_not_equal_suite                     \
  }

#define ARRAY_SUITE_LEN 19

#endif // SRC_TEST_S21_TESTS_SUITE_H_
