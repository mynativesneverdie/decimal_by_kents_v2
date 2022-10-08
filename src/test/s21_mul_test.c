#include "s21_tests_suite.h"

Suite *s21_mul_suite(void) {
  Suite *suite = suite_create("MUL test");

  TCase *tc_insert = tcase_create("mul_test");

  suite_add_tcase(suite, tc_insert);

  return suite;
}
