#include "s21_tests_suite.h"

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal value_1 = {{0, 18, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 18, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal value_1 = {{13, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal value_1 = {{165, 2, 0, 0}};
  s21_decimal value_2 = {{0, 1, 2, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal value_1 = {{0, 12, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{1, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{12, 0, 77, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{10, 151, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{5, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{12, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
  s21_decimal value_1 = {{5, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{12, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_9) {
  s21_decimal value_1 = {{12, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{12, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater_or_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_is_greater_or_equal_suite(void) {
  Suite *suite = suite_create("GREATER/EQUAL test");

  TCase *tc_insert = tcase_create("greater_or_equal_test");

  tcase_add_test(tc_insert, s21_is_greater_or_equal_1);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_2);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_3);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_4);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_5);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_6);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_7);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_8);
  tcase_add_test(tc_insert, s21_is_greater_or_equal_9);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
