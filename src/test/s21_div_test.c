#include "s21_tests_suite.h"

START_TEST(test_01_s21_div) {
  s21_decimal a = {{1444, 0, 0, 0x00000000}}, b = {{2, 0, 0, 0x00000000}},
              c = {{0x000002D2, 0x00000000, 0x00000000, 0x00000000}},
              res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_div(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_02_s21_div) {
  s21_decimal a = {{0, 0, 0, 0x00000000}}, b = {{2, 0, 0, 0x00000000}},
              c = {{0, 0, 0, 0x00000000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_div(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_03_s21_div) {
  s21_decimal a = {{423, 0, 0, 0x00000000}}, b = {{0, 0, 0, 0x00000000}},
              c = {{0, 0, 0, 0x00000000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_div(a, b, &res), DIV_BY_ZERO);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *suite = suite_create("DIV test");

  TCase *tc_insert = tcase_create("div_test");

  tcase_add_test(tc_insert, test_01_s21_div);
  tcase_add_test(tc_insert, test_02_s21_div);
  tcase_add_test(tc_insert, test_03_s21_div);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
