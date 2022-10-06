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
} END_TEST

START_TEST(test_02_s21_negate) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};

    int ret = s21_negate(value, &result);

    ck_assert_int_eq(result.bits[0], 1);
    ck_assert_int_eq(result.bits[1], 0);
    ck_assert_int_eq(result.bits[2], 0);
    ck_assert_int_eq(result.bits[3], SIGN_DECIMAL_MASK);
    ck_assert_int_eq(ret, 0);
} END_TEST

START_TEST(test_03_s21_negate) {
    s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal result = {{0, 0, 0, 0}};

    int ret = s21_negate(value, &result);

    ck_assert_int_eq(result.bits[0], UINT_MAX);
    ck_assert_int_eq(result.bits[1], UINT_MAX);
    ck_assert_int_eq(result.bits[2], UINT_MAX);
    ck_assert_int_eq(result.bits[3], SIGN_DECIMAL_MASK);
    ck_assert_int_eq(ret, 0);
} END_TEST

START_TEST(test_04_s21_negate) {
  s21_decimal value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0xFF0000 }};
  s21_decimal result = {{0, 0, 0, 0}};

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(ret, 1);
} END_TEST

Suite * s21_negate_suite(void) {
    Suite * suite = suite_create("NEGATE test");

    TCase * tc = tcase_create("negate_test");

    tcase_add_test(tc, test_01_s21_negate);
    tcase_add_test(tc, test_02_s21_negate);
    tcase_add_test(tc, test_03_s21_negate);
    tcase_add_test(tc, test_04_s21_negate);

    suite_add_tcase(suite, tc);

    return suite;
}
