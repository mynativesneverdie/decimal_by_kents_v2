#include "s21_tests_suite.h"

START_TEST(test_01_s21_sub) {
  s21_decimal value_1 = {{65, 0x00, 0x00, 0x000000}};
  s21_decimal value_2 = {{225, 0x00, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 160);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_02_s21_sub) {
  s21_decimal value_1 = {{36, 0x00, 0x00, 0x000000}};
  s21_decimal value_2 = {{9, 0x00, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 27);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_03_s21_sub) {
  s21_decimal value_1 = {{0xFFFFD8F0, 0x3C, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x00, 0x28, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFD8F0);
  ck_assert_int_eq(result.bits[1], 0x14);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_04_s21_sub) {
  s21_decimal value_1 = {{0xFFFFD8F0, 0x14, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x00, 0x14, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFD8F0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_05_s21_sub) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x00000000, 0xD8000000, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0x27FFFFFF);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_06_s21_sub) {
  s21_decimal value_1 = {{0x50, 0x00, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x36, 0x00, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x1A);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_07_s21_sub) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{0x00, 0x00, 0xD8000000, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0x27FFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_08_s21_sub) {
  s21_decimal value_1 = {{0x2342, 0x23FDECA, 0x00, 0x800A0000}};
  s21_decimal value_2 = {{0x4321, 0x5555, 0xD8000000, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x39D9DD5C);
  ck_assert_int_eq(result.bits[1], 0x00005551);
  ck_assert_int_eq(result.bits[2], 0xD8000000);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

START_TEST(test_09_s21_sub) {
  s21_decimal value_1 = {{0x2342, 0x23FDECA, 0x00, 0x800A0000}};
  s21_decimal value_2 = {{0x4321, 0x5555, 0xD8000000, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x7A3710E4);
  ck_assert_int_eq(result.bits[1], 0x9999A222);
  ck_assert_int_eq(result.bits[2], 0x15999999);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *suite = suite_create("SUB test");

  TCase *tc_insert = tcase_create("sub_test");

  tcase_add_test(tc_insert, test_01_s21_sub);
  tcase_add_test(tc_insert, test_02_s21_sub);
  tcase_add_test(tc_insert, test_03_s21_sub);
  tcase_add_test(tc_insert, test_04_s21_sub);
  tcase_add_test(tc_insert, test_05_s21_sub);
  tcase_add_test(tc_insert, test_06_s21_sub);
  tcase_add_test(tc_insert, test_07_s21_sub);
  tcase_add_test(tc_insert, test_08_s21_sub);
  tcase_add_test(tc_insert, test_09_s21_sub);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
