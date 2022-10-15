#include "s21_tests_suite.h"

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{0, 13, 18, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 13, 18, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{56, 18, 0, 0}};
  s21_decimal value_2 = {{56, 18, 1, 0}};

  int res = 0;
  int res1 = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}

START_TEST(s21_is_equal_5) {
  s21_decimal value_1 = {{2, 0, 0, FULL_EXP_DECIMAL_MASK}};
  s21_decimal value_2 = {{2, 0, 0, 0x1B0000}};

  int res = 0;
  int res1 = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}

Suite *s21_is_equal_suite(void) {
  Suite *suite = suite_create("EQUAL test");

  TCase *tc_insert = tcase_create("equal_test");

  tcase_add_test(tc_insert, s21_is_equal_1);
  tcase_add_test(tc_insert, s21_is_equal_2);
  tcase_add_test(tc_insert, s21_is_equal_3);
  tcase_add_test(tc_insert, s21_is_equal_4);
  tcase_add_test(tc_insert, s21_is_equal_5);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
