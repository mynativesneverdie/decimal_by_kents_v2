#include "s21_tests_suite.h"

START_TEST(test_01_s21_sub) {
  s21_decimal a = {{123, 0, 0, 0x00050000}}, b = {{456, 0, 0, 0x80050000}},
              c = {{579, 0, 0, 0x00050000}}, res = DECIMAL_ZERO;

  ck_assert_int_eq(s21_sub(a, b, &res), OK);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *suite = suite_create("SUB test");

  TCase *tc_insert = tcase_create("sub_test");

  tcase_add_test(tc_insert, test_01_s21_sub);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
