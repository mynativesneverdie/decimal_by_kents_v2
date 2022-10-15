#include "s21_tests_suite.h"

START_TEST(test_01_s21_negate) {
  s21_decimal value = {{1, 0, 0, SIGN_DECIMAL_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_02_s21_negate) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_DECIMAL_MASK);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_03_s21_negate) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(result.bits[0], UINT_MAX);
  ck_assert_int_eq(result.bits[1], UINT_MAX);
  ck_assert_int_eq(result.bits[2], UINT_MAX);
  ck_assert_int_eq(result.bits[3], SIGN_DECIMAL_MASK);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_04_s21_negate) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0xFF0000}};
  s21_decimal result = {{0, 0, 0, 0}};

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_negate_1) {
  int a = 10;
  s21_decimal res_a = DECIMAL_ZERO;
  s21_decimal src = DECIMAL_ZERO;
  int result = 0;
  s21_from_int_to_decimal(a, &src);
  s21_negate(src, &res_a);
  s21_from_decimal_to_int(res_a, &result);
  ck_assert_int_eq(-10, result);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal res_a = DECIMAL_ZERO;
  s21_decimal src = DECIMAL_ZERO;
  float result = 0;
  s21_from_float_to_decimal(10.12345, &src);
  s21_negate(src, &res_a);
  s21_from_decimal_to_float(res_a, &result);
  ck_assert_float_eq(-10.12345, result);
}
END_TEST

START_TEST(s21_negate_3) {
  float a = 10.1234e5;
  s21_decimal res_a = {0};
  s21_decimal src = {0};
  float result = 0;
  s21_from_float_to_decimal(a, &src);
  s21_negate(src, &res_a);
  s21_from_decimal_to_float(res_a, &result);
  ck_assert_float_eq(-10.1234e5, result);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *suite = suite_create("NEGATE test");

  TCase *tc = tcase_create("negate_test");

  tcase_add_test(tc, test_01_s21_negate);
  tcase_add_test(tc, test_02_s21_negate);
  tcase_add_test(tc, test_03_s21_negate);
  tcase_add_test(tc, test_04_s21_negate);
  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);
  tcase_add_test(tc, s21_negate_3);

  suite_add_tcase(suite, tc);

  return suite;
}
