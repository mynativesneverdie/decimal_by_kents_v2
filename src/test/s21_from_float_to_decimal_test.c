#include "s21_tests_suite.h"

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 123.456;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x075BCA01);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00060000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 116987.21930;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xB94C5453);
  ck_assert_int_eq(result.bits[1], 0x00000002);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00050000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 12623532.7256347;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00C09EAD);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = -342123124124321432143.6411;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x8BE98000);
  ck_assert_int_eq(result.bits[2], 0x00000012);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 126235235432532.7256123512347F;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x6E800000);
  ck_assert_int_eq(result.bits[1], 0x000072CF);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 1262351243126523463632.725633246234673247;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x6EA48000);
  ck_assert_int_eq(result.bits[2], 0x00000044);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = -234632612623532.7256347;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xAA000000);
  ck_assert_int_eq(result.bits[1], 0x0000D565);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 126.7256347;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x078DAE00);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00060000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 3.3333335;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x0032DCD5);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00060000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 2.2222225;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x0021E88F);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00060000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_11) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = 0;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_float_to_decimal_12) {
  s21_decimal result = DECIMAL_ZERO;
  float float_num = -0.231;

  ck_assert_int_eq(s21_from_float_to_decimal(float_num, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 231);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80030000);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *suite = suite_create("FROM_FLOAT_TO_DECIMAL test");

  TCase *tc = tcase_create("from_float_to_decimal_test");

  tcase_add_test(tc, s21_from_float_to_decimal_1);
  tcase_add_test(tc, s21_from_float_to_decimal_2);
  tcase_add_test(tc, s21_from_float_to_decimal_3);
  tcase_add_test(tc, s21_from_float_to_decimal_4);
  tcase_add_test(tc, s21_from_float_to_decimal_5);
  tcase_add_test(tc, s21_from_float_to_decimal_6);
  tcase_add_test(tc, s21_from_float_to_decimal_7);
  tcase_add_test(tc, s21_from_float_to_decimal_8);
  tcase_add_test(tc, s21_from_float_to_decimal_9);
  tcase_add_test(tc, s21_from_float_to_decimal_10);
  tcase_add_test(tc, s21_from_float_to_decimal_11);
  tcase_add_test(tc, s21_from_float_to_decimal_12);

  suite_add_tcase(suite, tc);

  return suite;
}
