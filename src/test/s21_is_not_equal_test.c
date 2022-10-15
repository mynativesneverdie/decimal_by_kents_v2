#include "s21_tests_suite.h"

START_TEST(s21_is_not_equal_1) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};

  int res = 0;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal value_1 = {{4, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal value_1 = {{37, 15, 15, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{37, 15, 15, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal value_1 = {{7, 1311, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{8, 0, 13, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal value_1 = {{151, 0, 0, 0}};
  s21_decimal value_2 = {{151, 0, 1, 0}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal value_1 = {{1511, 18, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{1511, 18, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal value_1 = {{1511, 18, 0, 0}};
  s21_decimal value_2 = {{0, 18, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_8) {
  s21_decimal value_1 = {{1511, 18, 0, 0}};
  s21_decimal value_2 = {{0, 18, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_9) {
  s21_decimal value_1 = {{0, 15, 666, 0}};
  s21_decimal value_2 = {{0, 0, 666, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_10) {
  s21_decimal value_1 = {{0, 0, 18, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{2, 0, 18, 0}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_11) {
  s21_decimal value_1 = {{0, 122, 0, 0}};
  s21_decimal value_2 = {{0x000000, 122, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_12) {
  s21_decimal value_1 = {{0, 122, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{10000, 0, 2011111, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_13) {
  s21_decimal value_1 = {{0, 122, 0, 0}};
  s21_decimal value_2 = {{1, 777773434, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_14) {
  s21_decimal value_1 = {{0, 122, 1555, 0}};
  s21_decimal value_2 = {{15, 0, 18, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_not_equal_15) {
  s21_decimal value_1 = {{7, 122, 0, 0}};
  s21_decimal value_2 = {{0, 122, 10, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_is_not_equal_suite(void) {
  Suite *suite = suite_create("NOT EQUAL test");

  TCase *tc_insert = tcase_create("not_equal_test");

  tcase_add_test(tc_insert, s21_is_not_equal_1);
  tcase_add_test(tc_insert, s21_is_not_equal_2);
  tcase_add_test(tc_insert, s21_is_not_equal_3);
  tcase_add_test(tc_insert, s21_is_not_equal_4);
  tcase_add_test(tc_insert, s21_is_not_equal_5);
  tcase_add_test(tc_insert, s21_is_not_equal_6);
  tcase_add_test(tc_insert, s21_is_not_equal_7);
  tcase_add_test(tc_insert, s21_is_not_equal_8);
  tcase_add_test(tc_insert, s21_is_not_equal_9);
  tcase_add_test(tc_insert, s21_is_not_equal_10);
  tcase_add_test(tc_insert, s21_is_not_equal_11);
  tcase_add_test(tc_insert, s21_is_not_equal_12);
  tcase_add_test(tc_insert, s21_is_not_equal_13);
  tcase_add_test(tc_insert, s21_is_not_equal_14);
  tcase_add_test(tc_insert, s21_is_not_equal_15);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
