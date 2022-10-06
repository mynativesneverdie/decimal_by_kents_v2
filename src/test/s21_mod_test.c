#include "s21_tests_suite.h"

#include "s21_tests_suite.h"

START_TEST(test_01_s21_mod) {
  s21_decimal value_2 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_1 = {{0, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x800D0000);
}
END_TEST

START_TEST(test_02_s21_mod) {
  s21_decimal value_1 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_2 = {{0, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), DIV_BY_ZERO);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_03_s21_mod) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_2 = {{0x01, 0, 0, 0x00050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), DIV_BY_ZERO);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_04_s21_mod) {
  s21_decimal value_1 = {{0x70000000, 0xB30310A7, 0xE22EA493, 0x000000}};
  s21_decimal value_2 = {{0x01, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), DIV_BY_ZERO);
  
  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_05_s21_mod) {
  s21_decimal value_1 = {{0x325223, 0x444444, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x018, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000008);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

START_TEST(test_06_s21_mod) {
  s21_decimal value_2 = {{0x325223, 0x444444, 0x00, 0x000000}};
  s21_decimal value_1 = {{0x8921B16D, 0x15555341, 0x00000002, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0xC490D8B5);
  ck_assert_int_eq(result.bits[1], 0x0AAAA9A0);
  ck_assert_int_eq(result.bits[2], 0x00000001);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

START_TEST(test_07_s21_mod) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_1 = {{0x8921B16D, 0x15555341, 0x00000002, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  
  ck_assert_int_eq(s21_mod(value_1, value_2, &result), SMALL_NUM);
  
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_08_s21_mod) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_2 = {{0x8921B16D, 0x15555341, 0x00000002, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0xD727E8CB);
  ck_assert_int_eq(result.bits[1], 0x0019C813);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_09_s21_mod) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  s21_decimal value_2 = {{0x8921B16D, 0x15555341, 0x00000002, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0xD727E8CB);
  ck_assert_int_eq(result.bits[1], 0x0019C813);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_10_s21_mod) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_11_s21_mod) {
  s21_decimal value_1 = {{0x323, 0x232, 0x00, 0x00000000}};
  s21_decimal value_2 = {{0x233, 0x2323, 0x232, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000323);
  ck_assert_int_eq(result.bits[1], 0x00000232);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_12_s21_mod) {
  s21_decimal value_1 = {{0x323, 0x232, 0x354334, 0x80000000}};
  s21_decimal value_2 = {{0x233, 0x2323, 0x232, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0xFFCAA7CA);
  ck_assert_int_eq(result.bits[1], 0xFCAB8808);
  ck_assert_int_eq(result.bits[2], 0x0000001D);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

Suite *s21_mod_suite(void) {
  Suite *suite = suite_create("MOD test");

  TCase *tc_insert = tcase_create("mod_test");

  tcase_add_test(tc_insert, test_01_s21_mod);
  tcase_add_test(tc_insert, test_02_s21_mod);
  tcase_add_test(tc_insert, test_03_s21_mod);
  tcase_add_test(tc_insert, test_04_s21_mod);
  tcase_add_test(tc_insert, test_05_s21_mod);
  tcase_add_test(tc_insert, test_06_s21_mod);
  tcase_add_test(tc_insert, test_07_s21_mod);
  tcase_add_test(tc_insert, test_08_s21_mod);
  tcase_add_test(tc_insert, test_09_s21_mod);
  tcase_add_test(tc_insert, test_10_s21_mod);
  tcase_add_test(tc_insert, test_11_s21_mod);
  tcase_add_test(tc_insert, test_12_s21_mod);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
