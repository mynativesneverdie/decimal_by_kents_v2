#include "s21_tests_suite.h"

START_TEST(s21_is_greater_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal value_1 = {{151, 3152, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 654, 0xFFFFFFFF, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal value_1 = {{0, 0, 13, 0}};
  s21_decimal value_2 = {{13, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal value_1 = {{13, 0, 13, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 81412, 167, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal value_1 = {{0, 11131, 167, 0}};
  s21_decimal value_2 = {{13, 5551, 13, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_8) {
  s21_decimal value_1 = {{0, 0, 121, 0}};
  s21_decimal value_2 = {{2, 12, 11, 0}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_9) {
  s21_decimal value_1 = {{0, 12, 150023, 0}};
  s21_decimal value_2 = {{12, 1, 1555, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_greater_10) {
  s21_decimal value_1 = {{12, 1, 1555, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{12, 1, 1555, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_greater(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_is_greater_suite(void) {
  Suite *suite = suite_create("GREATER test");

  TCase *tc_insert = tcase_create("greater_test");

  tcase_add_test(tc_insert, s21_is_greater_1);
  tcase_add_test(tc_insert, s21_is_greater_2);
  tcase_add_test(tc_insert, s21_is_greater_3);
  tcase_add_test(tc_insert, s21_is_greater_4);
  tcase_add_test(tc_insert, s21_is_greater_5);
  tcase_add_test(tc_insert, s21_is_greater_6);
  tcase_add_test(tc_insert, s21_is_greater_7);
  tcase_add_test(tc_insert, s21_is_greater_8);
  tcase_add_test(tc_insert, s21_is_greater_9);
  tcase_add_test(tc_insert, s21_is_greater_10);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
