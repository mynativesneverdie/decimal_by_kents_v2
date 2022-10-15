#include "s21_tests_suite.h"

START_TEST(test_01_s21_add) {
  s21_decimal a = {{123, 0, 0, 0x00050000}}, b = {{456, 0, 0, 0x00050000}},
              c = {{579, 0, 0, 0x00050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_02_s21_add) {
  s21_decimal a = {{123, 0, 0, 0x80050000}}, b = {{456, 0, 0, 0x00050000}},
              c = {{333, 0, 0, 0x00050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_03_s21_add) {
  s21_decimal a = {{555, 0, 0, 0x80050000}}, b = {{456, 0, 0, 0x00050000}},
              c = {{99, 0, 0, 0x80050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_04_s21_add) {
  s21_decimal a = {{123, 0, 0, 0x00050000}}, b = {{456, 0, 0, 0x80050000}},
              c = {{333, 0, 0, 0x80050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_05_s21_add) {
  s21_decimal a = {{555, 0, 0, 0x00050000}}, b = {{456, 0, 0, 0x80050000}},
              c = {{99, 0, 0, 0x00050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_06_s21_add) {
  s21_decimal a = {{555, 55, 0, 0x00050000}}, b = {{456, 55, 0, 0x80050000}},
              c = {{99, 0, 0, 0x00050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_07_s21_add) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
              b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
              c = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
              res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), SMALL_NUM);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_08_s21_add) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x801C0000}},
              b = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x801D0000}},
              c = {{0x99999999, 0x19999999, 0x00000001, 0x801C0000}},
              res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_09_s21_add) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00050000}},
              b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00050000}},
              c = {{0x33333334, 0x33333333, 0x33333333, 0x00040000}},
              res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(test_10_s21_add) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00090000}},
              b = {{0x23423423, 0xFFFFFFFF, 0xFFFFFFFF, 0x00090000}},
              c = {{0x1D20386A, 0x33333333, 0x33333333, 0x00080000}},
              res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_add(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *suite = suite_create("ADD test");

  TCase *tc_insert = tcase_create("add_test");

  tcase_add_test(tc_insert, test_01_s21_add);
  tcase_add_test(tc_insert, test_02_s21_add);
  tcase_add_test(tc_insert, test_03_s21_add);
  tcase_add_test(tc_insert, test_04_s21_add);
  tcase_add_test(tc_insert, test_05_s21_add);
  tcase_add_test(tc_insert, test_06_s21_add);
  tcase_add_test(tc_insert, test_07_s21_add);
  tcase_add_test(tc_insert, test_08_s21_add);
  tcase_add_test(tc_insert, test_09_s21_add);
  tcase_add_test(tc_insert, test_10_s21_add);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
