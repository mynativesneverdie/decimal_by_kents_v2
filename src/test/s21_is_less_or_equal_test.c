#include "s21_tests_suite.h"

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{13, 7, 12, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{15, 9, 9, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{20, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{19, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{15, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{15, 15, 15, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{15, 15, 15, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{15, 0, 19, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{15, 0, 17, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_is_less_or_equal_suite(void) {
  Suite *suite = suite_create("LESS/EQUAL test");

  TCase *tc_insert = tcase_create("less_or_equal_test");

  tcase_add_test(tc_insert, s21_is_less_or_equal_1);
  tcase_add_test(tc_insert, s21_is_less_or_equal_2);
  tcase_add_test(tc_insert, s21_is_less_or_equal_3);
  tcase_add_test(tc_insert, s21_is_less_or_equal_4);
  tcase_add_test(tc_insert, s21_is_less_or_equal_5);
  tcase_add_test(tc_insert, s21_is_less_or_equal_6);
  tcase_add_test(tc_insert, s21_is_less_or_equal_7);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
