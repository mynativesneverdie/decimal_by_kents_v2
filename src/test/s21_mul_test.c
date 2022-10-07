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
  s21_decimal value_1 = {{0x97B425E5, 0x7B425ED0, 0x9425ED09, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), LARGE_NUM);
  // s21_mul(value_1, value_2, &result);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);


  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_05_s21_mul) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_06_s21_mul) {
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

START_TEST(test_07_s21_mul) {
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

START_TEST(test_08_s21_mul) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal value_2 = {{0x201241, 0, 0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), LARGE_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_09_s21_mul) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal value_1 = {{0x201241, 0, 0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), LARGE_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_10_s21_mul) {
  s21_decimal value_2 = {{0x11111111, 0x11111111, 0x11111111, 0x00000000}};
  s21_decimal value_1 = {{0x767, 0, 0, 0x800A0000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x22222222);
  ck_assert_int_eq(result.bits[1], 0x22222222);
  ck_assert_int_eq(result.bits[2], 0x22222222);
  ck_assert_int_eq(result.bits[3], 0x80070000);
}
END_TEST

START_TEST(test_11_s21_mul) {
  s21_decimal value_2 = {{0x11111111, 0x11111111, 0x1111111, 0x00000000}};
  s21_decimal value_1 = {{0x767, 0, 0, 0x80040000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x44444443);
  ck_assert_int_eq(result.bits[1], 0x44444444);
  ck_assert_int_eq(result.bits[2], 0x14444444);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_12_s21_mul) {
  s21_decimal value_1 = {{0x11111111, 0x11111111, 0x1111111, 0x00000000}};
  s21_decimal value_2 = {{0x767, 0, 0, 0x80040000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);
  // s21_mul(value_1, value_2, &result);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x44444443);
  ck_assert_int_eq(result.bits[1], 0x44444444);
  ck_assert_int_eq(result.bits[2], 0x14444444);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_13_s21_mul) {
  s21_decimal value_1 = {{0x232312, 0x11111111, 0x1111111, 0x000A0000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00110000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), OK_STATUS);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x083D847E);
  ck_assert_int_eq(result.bits[1], 0x812A16A2);
  ck_assert_int_eq(result.bits[2], 0x548291FB);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_14_s21_mul) {
  s21_decimal value_1 = {{0x232312, 0x11111111, 0x1111111, 0x00000000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), LARGE_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_15_s21_mul) {
  s21_decimal value_2 = {{0x232312, 0x11111111, 0x1111111, 0x00000000}};
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), LARGE_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST


START_TEST(test_16_s21_mul) {
  s21_decimal value_2 = {{0x01, 0x00, 0x00, 0x00030000}};
  s21_decimal value_1 = {{0x4234234, 0x32342, 0x324342, 0x80C10000}};
  s21_decimal result = {{0, 0, 0, 0}};
  

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), SMALL_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_17_s21_mul) {
  s21_decimal value_2 = {{0x3423, 0x00000000, 0x00000000, 0x00C10000}};
  s21_decimal value_1 = {{0x232312, 0x232312, 0x232312, 0x00C10000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), SMALL_NUM);
  // printf("%08X %08X%08X%08X\n", result.bits[3], result.bits[2], result.bits[1], result.bits[0]);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST


Suite *s21_mul_suite(void) {
  Suite *suite = suite_create("MUL test");

  TCase *tc_insert = tcase_create("mul_test");

  // tcase_add_test(tc_insert, test_01_s21_mul);
  // tcase_add_test(tc_insert, test_02_s21_mul);
  // tcase_add_test(tc_insert, test_03_s21_mul);
  // tcase_add_test(tc_insert, test_04_s21_mul);
  // tcase_add_test(tc_insert, test_05_s21_mul);
  // tcase_add_test(tc_insert, test_06_s21_mul);
  // tcase_add_test(tc_insert, test_07_s21_mul);
  // tcase_add_test(tc_insert, test_08_s21_mul);
  // tcase_add_test(tc_insert, test_09_s21_mul);
  // tcase_add_test(tc_insert, test_10_s21_mul);
  // tcase_add_test(tc_insert, test_11_s21_mul);
  // tcase_add_test(tc_insert, test_12_s21_mul);
  // tcase_add_test(tc_insert, test_13_s21_mul);
  // tcase_add_test(tc_insert, test_14_s21_mul);
  // tcase_add_test(tc_insert, test_15_s21_mul);
  // tcase_add_test(tc_insert, test_16_s21_mul);
  // tcase_add_test(tc_insert, test_17_s21_mul);
  

  suite_add_tcase(suite, tc_insert);

  return suite;
}
