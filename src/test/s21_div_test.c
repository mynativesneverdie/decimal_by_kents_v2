#include "s21_tests_suite.h"

START_TEST(test_01_s21_div) {
  s21_decimal value_1 = {{10000, 0, 0, 0x000000}};
  s21_decimal value_2 = {{10, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 1000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_02_s21_div) {
  s21_decimal value_1 = {{0x00002710, 0x0001E0F3, 0x01, 0x000000}};
  s21_decimal value_2 = {{10, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x2710);
  ck_assert_int_eq(result.bits[1], 0x1E0F3);
  ck_assert_int_eq(result.bits[2], 0x01);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(test_03_s21_div) {
  s21_decimal value_1 = {{0x00002710, 0x0001E0F3, 0, 0x000000}};
  s21_decimal value_2 = {{10, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x2710);
  ck_assert_int_eq(result.bits[1], 0x1E0F3);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(test_04_s21_div) {
  s21_decimal value_1 = {{10, 0, 0, 0x000000}};
  s21_decimal value_2 = {{3, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x35555555);
  ck_assert_int_eq(result.bits[1], 0xCF2607EE);
  ck_assert_int_eq(result.bits[2], 0x6BB4AFE4);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_05_s21_div) {
  s21_decimal value_1 = {{0x00002710, 0x0001E0F3, 0x3242342, 0x000000}};
  s21_decimal value_2 = {{10, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x2710);
  ck_assert_int_eq(result.bits[1], 0x1E0F3);
  ck_assert_int_eq(result.bits[2], 0x03242342);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(test_06_s21_div) {
  s21_decimal value_1 = {{0x00002710, 0x0001E0F3, 0x3242342, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x685180D5);
  ck_assert_int_eq(result.bits[1], 0xBDE6C457);
  ck_assert_int_eq(result.bits[2], 0x7456E0F4);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

START_TEST(test_07_s21_div) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x425ED097);
  ck_assert_int_eq(result.bits[1], 0x25ED097B);
  ck_assert_int_eq(result.bits[2], 0x5ED097B4);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(test_08_s21_div) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x0FD9A238);
  ck_assert_int_eq(result.bits[1], 0x5ED097B4);
  ck_assert_int_eq(result.bits[2], 0x16136742);
  ck_assert_int_eq(result.bits[3], 0x000A0000);
}
END_TEST

START_TEST(test_09_s21_div) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x77971C71);
  ck_assert_int_eq(result.bits[1], 0x09289DB2);
  ck_assert_int_eq(result.bits[2], 0x336632E5);
  ck_assert_int_eq(result.bits[3], 0x00140000);
}
END_TEST

START_TEST(test_10_s21_div) {
  s21_decimal value_1 = {{0x324532, 0x123213, 0, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x948F6D09);
  ck_assert_int_eq(result.bits[1], 0x632BE5E1);
  ck_assert_int_eq(result.bits[2], 0x3D4AB7C6);
  ck_assert_int_eq(result.bits[3], 0x000E0000);
}
END_TEST

START_TEST(test_11_s21_div) {
  s21_decimal value_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0x27FFFFFF, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x97B425E5);
  ck_assert_int_eq(result.bits[1], 0x7B425ED0);
  ck_assert_int_eq(result.bits[2], 0x9425ED09);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_12_s21_div) {
  s21_decimal value_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x425ED096);
  ck_assert_int_eq(result.bits[1], 0x25ED097B);
  ck_assert_int_eq(result.bits[2], 0x5ED097B4);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(test_13_s21_div) {
  s21_decimal value_2 = {{0x3241, 0x322, 0x00, 0x000000}};
  s21_decimal value_1 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xE0AEB5B6);
  ck_assert_int_eq(result.bits[1], 0x01167A2D);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_14_s21_div) {
  s21_decimal value_2 = {{0x3241, 0x322, 0x00, 0x80000000}};
  s21_decimal value_1 = {{27, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xE0AEB5B6);
  ck_assert_int_eq(result.bits[1], 0x01167A2D);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x801C0000);
}
END_TEST

START_TEST(test_15_s21_div) {
  s21_decimal value_2 = {{0x3241, 0x322, 0x00, 0x80000000}};
  s21_decimal value_1 = {{27, 0, 0, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xE0AEB5B6);
  ck_assert_int_eq(result.bits[1], 0x01167A2D);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_16_s21_div) {
  s21_decimal value_2 = {{0x3241, 0x322, 0x00, 0x001C0000}};
  s21_decimal value_1 = {{27, 0, 0, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x3D279B0E);
  ck_assert_int_eq(result.bits[1], 0xC6C29A9F);
  ck_assert_int_eq(result.bits[2], 0x1953CDD4);
  ck_assert_int_eq(result.bits[3], 0x800B0000);
}
END_TEST

START_TEST(test_17_s21_div) {
  s21_decimal value_2 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_1 = {{0x3421, 0x5432, 0, 0x80050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xBC8AE92D);
  ck_assert_int_eq(result.bits[1], 0x0F58F910);
  ck_assert_int_eq(result.bits[2], 0x1FE19DC9);
  ck_assert_int_eq(result.bits[3], 0x00140000);
}
END_TEST

START_TEST(test_18_s21_div) {
  s21_decimal value_1 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_2 = {{0x3421, 0x5432, 0x00, 0x80050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xC52F625F);
  ck_assert_int_eq(result.bits[1], 0x7E83E0AD);
  ck_assert_int_eq(result.bits[2], 0x00000005);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_19_s21_div) {
  s21_decimal value_1 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_2 = {{0, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), DIV_BY_ZERO);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_20_s21_div) {
  s21_decimal value_2 = {{0xDD02, 0x5555, 0x00, 0x800D0000}};
  s21_decimal value_1 = {{0, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_21_s21_div) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_2 = {{0x01, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], UINT_MAX);
  ck_assert_int_eq(result.bits[1], UINT_MAX);
  ck_assert_int_eq(result.bits[2], UINT_MAX);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_22_s21_div) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_2 = {{0x01, 0, 0, 0x00050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), DIV_BY_ZERO);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_23_s21_div) {
  s21_decimal value_1 = {{0xDD02, 0x5555, 0x00, 0x000D01}};
  s21_decimal value_2 = {{0, 0, 0, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), DIV_BY_ZERO);

  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_24_s21_div) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal value_2 = {{0x05, 0, 0, 0x00050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), DIV_BY_ZERO);
  
  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_25_s21_div) {
  s21_decimal value_1 = {{0x55, 0x55, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x55, 0x55, 0x55, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x3E250260);
  ck_assert_int_eq(result.bits[1], 0x204FCE5E);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_26_s21_div) {
  s21_decimal value_1 = {{0x55, 0x55, 0x00, 0x000000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), SMALL_NUM);
  
  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_27_s21_div) {
  s21_decimal value_1 = {{0x55, 0x55, 0x00, 0x000000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), SMALL_NUM);
  
  ck_assert_int_eq(result.bits[0], 0x00);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00);
}
END_TEST

START_TEST(test_28_s21_div) {
  s21_decimal value_1 = {{0x325223, 0x444444, 0x00, 0x000000}};
  s21_decimal value_2 = {{0x019, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x07DCD578);
  ck_assert_int_eq(result.bits[1], 0x0AAAAAA0);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_29_s21_div) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_30_s21_div) {
  s21_decimal value_1 = {{0x11111111, 0x22222222, 0x33333333, 0x00C10000}};
  s21_decimal value_2 = {{0x11111111, 0x33333333, 0x33333333, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_31_s21_div) {
  s21_decimal value_2 = {{0x11111111, 0x22222222, 0x3333333, 0x00040000}};
  s21_decimal value_1 = {{0xCCCCCCCC, 0xCCCCCCCC, 0xFFFFFFFF, 0x000D0000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(test_32_s21_div) {
  s21_decimal value_1 = {{0x000F7274, 0x00, 0x00, 0x00030000}};
  s21_decimal value_2 = {{0xA, 0x00, 0x00, 0x00000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), OK_STATUS);
  
  ck_assert_int_eq(result.bits[0], 0x00018B72);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *suite = suite_create("DIV test");

  TCase *tc_insert = tcase_create("div_test");

  // tcase_add_test(tc_insert, test_01_s21_div);
  // tcase_add_test(tc_insert, test_02_s21_div);
  // tcase_add_test(tc_insert, test_03_s21_div);
  // tcase_add_test(tc_insert, test_04_s21_div);
  // tcase_add_test(tc_insert, test_05_s21_div);
  // tcase_add_test(tc_insert, test_06_s21_div);
  // tcase_add_test(tc_insert, test_07_s21_div);
  // tcase_add_test(tc_insert, test_08_s21_div);
  // tcase_add_test(tc_insert, test_09_s21_div);
  // tcase_add_test(tc_insert, test_10_s21_div);
  // tcase_add_test(tc_insert, test_11_s21_div);
  // tcase_add_test(tc_insert, test_12_s21_div);
  // tcase_add_test(tc_insert, test_13_s21_div);
  // tcase_add_test(tc_insert, test_14_s21_div);
  // tcase_add_test(tc_insert, test_15_s21_div);
  // tcase_add_test(tc_insert, test_16_s21_div);
  // tcase_add_test(tc_insert, test_17_s21_div);
  // tcase_add_test(tc_insert, test_18_s21_div);
  // tcase_add_test(tc_insert, test_19_s21_div);
  // tcase_add_test(tc_insert, test_20_s21_div);
  // tcase_add_test(tc_insert, test_21_s21_div);
  // tcase_add_test(tc_insert, test_22_s21_div);
  // tcase_add_test(tc_insert, test_23_s21_div);
  // tcase_add_test(tc_insert, test_24_s21_div);
  // tcase_add_test(tc_insert, test_25_s21_div);
  // tcase_add_test(tc_insert, test_26_s21_div);
  // tcase_add_test(tc_insert, test_27_s21_div);
  // tcase_add_test(tc_insert, test_28_s21_div);
  // tcase_add_test(tc_insert, test_29_s21_div);
  // tcase_add_test(tc_insert, test_30_s21_div);
  // tcase_add_test(tc_insert, test_31_s21_div);
  // tcase_add_test(tc_insert, test_32_s21_div);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
