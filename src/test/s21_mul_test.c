#include "s21_tests_suite.h"

START_TEST(test_01_s21_mul) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 130);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_02_s21_mul) {
  s21_decimal value_1 = {{0x4CCCD0B4, 0x3018, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00002708);
  ck_assert_int_eq(result.bits[1], 0x0001E0F3);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_03_s21_mul) {
  s21_decimal value_1 = {{0x3C, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000258);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_04_s21_mul) {
  s21_decimal value_1 = {{0x52231, 0x233, 0, 1}};
  s21_decimal value_2 = {{1241, 0, 0, 1}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x18E2BF89);
  ck_assert_int_eq(result.bits[1], 0x000AA93B);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_05_s21_mul) {
  s21_decimal value_1 = {{0x52231, 0x233, 0, 1}};
  s21_decimal value_2 = {{1241, 0, 0, 1}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x18E2BF89);
  ck_assert_int_eq(result.bits[1], 0x000AA93B);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *suite = suite_create("MUL test");

  TCase *tc_insert = tcase_create("mul_test");

  tcase_add_test(tc_insert, test_01_s21_mul);
  tcase_add_test(tc_insert, test_02_s21_mul);
  tcase_add_test(tc_insert, test_03_s21_mul);
  tcase_add_test(tc_insert, test_04_s21_mul);
  tcase_add_test(tc_insert, test_05_s21_mul);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
