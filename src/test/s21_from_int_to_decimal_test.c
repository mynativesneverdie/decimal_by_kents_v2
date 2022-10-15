#include "s21_tests_suite.h"

START_TEST(test_01_s21_from_int_to_decimal) {
  s21_decimal result = DECIMAL_ZERO;
  int int_num = 231;

  ck_assert_int_eq(s21_from_int_to_decimal(int_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x000000E7);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_02_s21_from_int_to_decimal) {
  s21_decimal result = DECIMAL_ZERO;
  int int_num = -231;

  ck_assert_int_eq(s21_from_int_to_decimal(int_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x000000E7);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_03_s21_from_int_to_decimal) {
  s21_decimal result = DECIMAL_ZERO;
  long unsigned int int_num = 0xFFFFFFFFFFFFFFFFFF;

  ck_assert_int_eq(s21_from_int_to_decimal(int_num, &result), OK_STATUS);
  //   printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2],
  //   result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_04_s21_from_int_to_decimal) {
  s21_decimal result = DECIMAL_ZERO;
  int int_num = INT_MAX;

  ck_assert_int_eq(s21_from_int_to_decimal(int_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], INT_MAX);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_05_s21_from_int_to_decimal) {
  s21_decimal result = DECIMAL_ZERO;
  int int_num = 0;

  ck_assert_int_eq(s21_from_int_to_decimal(int_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *suite = suite_create("FROM_INT_TO_DECIMAL test");

  TCase *tc_insert = tcase_create("from_int_to_decimal_test");

  tcase_add_test(tc_insert, test_01_s21_from_int_to_decimal);
  tcase_add_test(tc_insert, test_02_s21_from_int_to_decimal);
  tcase_add_test(tc_insert, test_03_s21_from_int_to_decimal);
  tcase_add_test(tc_insert, test_04_s21_from_int_to_decimal);
  tcase_add_test(tc_insert, test_05_s21_from_int_to_decimal);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
