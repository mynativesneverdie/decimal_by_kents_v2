#include "s21_tests_suite.h"

START_TEST(test_01_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x00, 0x00, 0x00000000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 8978);
}
END_TEST

START_TEST(test_02_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x00, 0x00, 0x80000000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, -8978);
}
END_TEST

START_TEST(test_03_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x00, 0x00, 0x00020000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 89);
}
END_TEST

START_TEST(test_04_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x00, 0x00, 0x80020000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, -89);
}
END_TEST

START_TEST(test_05_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x055, 0x00, 0x00000000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CONV_ERROR);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_06_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x00, 0x55, 0x00000000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CONV_ERROR);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_07_s21_from_decimal_to_int) {
  s21_decimal src = {{0x2312, 0x343, 0x55, 0x00000000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CONV_ERROR);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_08_s21_from_decimal_to_int) {
  s21_decimal src = {{UINT_MAX, 0x00, 0x00, 0x00080000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 42);
}
END_TEST

START_TEST(test_09_s21_from_decimal_to_int) {
  s21_decimal src = {{UINT_MAX, 0x00, 0x00, 0x000A0000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_10_s21_from_decimal_to_int) {
  s21_decimal src = {{UINT_MAX, 0x00, 0x00, 0x001C0000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_11_s21_from_decimal_to_int) {
  s21_decimal src = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x001C0000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), OK_STATUS);
  ck_assert_int_eq(dst, 7);
}
END_TEST

START_TEST(test_12_s21_from_decimal_to_int) {
  s21_decimal src = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00C10000}};
  int dst = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CONV_ERROR);
  ck_assert_int_eq(dst, 0);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *suite = suite_create("FROM_DECIMAL_TO_INT test");

  TCase *tc_insert = tcase_create("from_decimal_to_int_test");

  tcase_add_test(tc_insert, test_01_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_02_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_03_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_04_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_05_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_06_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_07_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_08_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_09_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_10_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_11_s21_from_decimal_to_int);
  tcase_add_test(tc_insert, test_12_s21_from_decimal_to_int);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
