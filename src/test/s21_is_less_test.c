#include "s21_tests_suite.h"

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{0, 15, 0, SIGN_DECIMAL_MASK}}; // 64424509440
  s21_decimal value_2 = {{1, 0, 0, SIGN_DECIMAL_MASK}};  //

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {{1, 15, 0, 0}};
  s21_decimal value_2 = {{0x0000000F, 0x00000001, 0, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{151, 13, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {{13, 13, 37, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{0, 0, 0, 0}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {{5, 8, 13, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal value_1 = {{7, 1311, 0, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{8, 0, 13, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal value_1 = {{2, 0, 121, 0}};
  s21_decimal value_2 = {{0, 12, 11, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal value_1 = {{0, 12, 0, 0}};
  s21_decimal value_2 = {{12, 1, 1555, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_9) {
  s21_decimal value_1 = {{12, 1, 1555, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{12, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_10) {
  s21_decimal value_1 = {{11, 1455, 111112, 0}};
  s21_decimal value_2 = {{11, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_11) {
  s21_decimal value_1 = {{11, 1455, 12344, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{11, 1455, 0, 0}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_12) {
  s21_decimal value_1 = {{11, 1455, 1344, 0}};
  s21_decimal value_2 = {{11, 0, 0, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_13) {
  s21_decimal value_1 = {{1, 222, 1011, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{14, 12, 01, 0}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_14) {
  s21_decimal value_1 = {{0, 15, 15, 0}};
  s21_decimal value_2 = {{1222, 0x00000, 0, SIGN_DECIMAL_MASK}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_15) {
  s21_decimal value_1 = {{85847, 12, 12, 0}};
  s21_decimal value_2 = {{0, 10, 10, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_16) {
  s21_decimal value_1 = {{12, 0, 10, SIGN_DECIMAL_MASK}};
  s21_decimal value_2 = {{1, 0, 0, SIGN_DECIMAL_MASK}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_17) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_18) {
  s21_decimal value_1 = {{12, 7, 2, 0x00010000}};
  s21_decimal value_2 = {{12, 7, 2, 0x00020000}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_19) {
  s21_decimal value_1 = {{
      1222,
      12,
      676,
      0x00020000,
  }};
  s21_decimal value_2 = {{1222, 12, 676, 0x00010000}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_20) {
  s21_decimal value_1 = {{
      1222,
      12,
      676,
      0x000A0000,
  }};
  s21_decimal value_2 = {{1222, 0, 0, 0x00020000}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_21) {
  s21_decimal value_1 = {{
      1222,
      12,
      676,
      0x00120000,
  }};
  s21_decimal value_2 = {{1222, 0, 0, 0x00020000}};

  int res = 0;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_is_less_22) {
  s21_decimal value_1 = {{
      1222,
      0,
      0,
      0x00020000,
  }};
  s21_decimal value_2 = {{1222, 12, 676, 0x00120000}};

  int res = 1;
  int res1 = s21_is_less(value_1, value_2);

  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_is_less_suite(void) {
  Suite *suite = suite_create("LESS test");

  TCase *tc_insert = tcase_create("less_test");

  tcase_add_test(tc_insert, s21_is_less_1);
  tcase_add_test(tc_insert, s21_is_less_2);
  tcase_add_test(tc_insert, s21_is_less_3);
  tcase_add_test(tc_insert, s21_is_less_4);
  tcase_add_test(tc_insert, s21_is_less_5);
  tcase_add_test(tc_insert, s21_is_less_6);
  tcase_add_test(tc_insert, s21_is_less_7);
  tcase_add_test(tc_insert, s21_is_less_8);
  tcase_add_test(tc_insert, s21_is_less_9);
  tcase_add_test(tc_insert, s21_is_less_10);
  tcase_add_test(tc_insert, s21_is_less_11);
  tcase_add_test(tc_insert, s21_is_less_12);
  tcase_add_test(tc_insert, s21_is_less_13);
  tcase_add_test(tc_insert, s21_is_less_14);
  tcase_add_test(tc_insert, s21_is_less_15);
  tcase_add_test(tc_insert, s21_is_less_16);
  tcase_add_test(tc_insert, s21_is_less_17);
  tcase_add_test(tc_insert, s21_is_less_18);
  tcase_add_test(tc_insert, s21_is_less_19);
  tcase_add_test(tc_insert, s21_is_less_20);
  tcase_add_test(tc_insert, s21_is_less_21);
  tcase_add_test(tc_insert, s21_is_less_22);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
