#include "s21_tests_suite.h"

START_TEST(test_01_s21_add) {
  s21_decimal value_1 = {{2654342324, 0, 0, 0x00020000}};
  s21_decimal value_2 = {{2342423432, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x12678004);
  ck_assert_int_eq(result.bits[1], 0x06);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_02_s21_add) {
  s21_decimal value_1 = {{2654342324, 0, 0, 0x80020000}};
  s21_decimal value_2 = {{2342423432, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x12678004);
  ck_assert_int_eq(result.bits[1], 0x06);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_03_s21_add) {
  s21_decimal value_1 = {{2654342324, 0, 0, 0x00020000}};
  s21_decimal value_2 = {{2342423432, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xD5FB669C);
  ck_assert_int_eq(result.bits[1], 0x04);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_04_s21_add) {
  s21_decimal value_1 = {{2654342324, 0, 0, 0x80020000}};
  s21_decimal value_2 = {{2342423432, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xD5FB669C);
  ck_assert_int_eq(result.bits[1], 0x04);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_05_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0, 0x00020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xB5C3);
  ck_assert_int_eq(result.bits[1], 0x12678004);
  ck_assert_int_eq(result.bits[2], 0x06);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_06_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0, 0x80020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xB5C3);
  ck_assert_int_eq(result.bits[1], 0x12678004);
  ck_assert_int_eq(result.bits[2], 0x06);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_07_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0, 0x80020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x9CAD);
  ck_assert_int_eq(result.bits[1], 0xD5FB669C);
  ck_assert_int_eq(result.bits[2], 0x04);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_08_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0, 0x00020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x9CAD);
  ck_assert_int_eq(result.bits[1], 0xD5FB669C);
  ck_assert_int_eq(result.bits[2], 0x04);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_09_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0x03C5, 0x00020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0x32FF, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xB5C3);
  ck_assert_int_eq(result.bits[1], 0x12678004);
  ck_assert_int_eq(result.bits[2], 0x201C1);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_10_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0x03C5, 0x80020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0x32FF, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xB5C3);
  ck_assert_int_eq(result.bits[1], 0x12678004);
  ck_assert_int_eq(result.bits[2], 0x201C1);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_11_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0x03C5, 0x80020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0x32FF, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x9CAD);
  ck_assert_int_eq(result.bits[1], 0xD5FB669C);
  ck_assert_int_eq(result.bits[2], 0x1FA35);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(test_12_s21_add) {
  s21_decimal value_1 = {{0x00000C8B, 0x9E360CB4, 0x03C5, 0x00020000}};
  s21_decimal value_2 = {{0x000010EC, 0x8B9E8B88, 0x32FF, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x9CAD);
  ck_assert_int_eq(result.bits[1], 0xD5FB669C);
  ck_assert_int_eq(result.bits[2], 0x1FA35);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(test_13_s21_add) {
  s21_decimal value_1 = {{0x01, 0x00, 0x01, 0x000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_14_s21_add) {
  s21_decimal value_1 = {{0x01, 0x00, 0x01, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_15_s21_add) {
  s21_decimal value_1 = {{0x01, 0x00, 0x01, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFD);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_16_s21_add) {
  s21_decimal value_1 = {{0x01, 0x00, 0x01, 0x000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFD);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_17_s21_add) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{0x06, 0x00, 0x00, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_18_s21_add) {
  s21_decimal value_1 = {{36, 0, 0, 0x000000}};
  s21_decimal value_2 = {{9, 0, 0, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0x1B);
  ck_assert_int_eq(result.bits[1], 0x00);
  ck_assert_int_eq(result.bits[2], 0x00);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_19_s21_add) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{0x06, 0x00, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_20_s21_add) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_1 = {{0x06, 0x00, 0x00, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_21_s21_add) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {{0x06, 0x00, 0x00, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_22_s21_add) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00040000}};
  s21_decimal value_1 = {{0x06, 0x00, 0x00, 0x80020000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFDA7);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00040000);
}
END_TEST

START_TEST(test_23_s21_add) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_1 = {{0x06, 0x00, 0x00, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_24_s21_add) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x000000}};
  s21_decimal value_1 = {{0x01, 0x00, 0x00, 0x00}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 1);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_25_s21_add) {
  s21_decimal value_2 = {{0x01, 0x00, 0x00, 0x000000}};
  s21_decimal value_1 = {{0x01, 0x00, 0x00, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_26_s21_add) {
  s21_decimal value_2 = {{0xED097AF2, 0xD097B425, 0xC97B425E, 0x000000}};
  s21_decimal value_1 = {{0xBDA12F28, 0xDA12F684, 0xA12F684B, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), LARGE_NUM);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_27_s21_add) {
  s21_decimal value_2 = {{0x2F684BCA, 0xF684BDA1, 0x284BDA12, 0x000000}};
  s21_decimal value_1 = {{0xBDA12F28, 0xDA12F684, 0xA12F684B, 0x000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xED097AF2);
  ck_assert_int_eq(result.bits[1], 0xD097B425);
  ck_assert_int_eq(result.bits[2], 0xC97B425E);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_28_s21_add) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x000000}};
  s21_decimal value_2 = {{0xAE123456, 0x34, 0x00, 0x800C0000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);

  ck_assert_int_eq(result.bits[0], 0xFFFFFFFD);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_29_s21_add) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00070000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);
  ck_assert_int_eq(result.bits[0], 0x374BC6A8);
  ck_assert_int_eq(result.bits[1], 0xE5604189);
  ck_assert_int_eq(result.bits[2], 0x19DB22D0);
  ck_assert_int_eq(result.bits[3], 0x00040000);
}
END_TEST

START_TEST(test_30_s21_add) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xAFFAFFFF, 0x00070000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFD, 0x00050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(value_1, value_2, &result), OK_STATUS);
  ck_assert_int_eq(result.bits[0], 0xDB22D0E5);
  ck_assert_int_eq(result.bits[1], 0xBC6A7EF9);
  ck_assert_int_eq(result.bits[2], 0x19C6A6A7);
  ck_assert_int_eq(result.bits[3], 0x00040000);
}
END_TEST

START_TEST(add) {
  s21_decimal a = {{123, 0, 0, 0}}, 
              b = {{456, 0, 0, 0}},
              c = {{579, 0, 0, 0}},
              res = DECIMAL_ZERO;
  set_scale(&a, 5);
  set_scale(&b, 5);
  set_scale(&c, 5);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(first_negative_add) {
  s21_decimal a = {{123, 0, 0, 0}},
              b = {{456, 0, 0, 0}},
              c = {{333, 0, 0, 0}},
              res = DECIMAL_ZERO;
  set_scale(&a, 5);
  set_scale(&b, 5);
  set_scale(&c, 5);
  set_sign(&a, 1);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(first_negative_add_1) {
  s21_decimal a = {{555, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{99, 0, 0, 0}},
              res = DECIMAL_ZERO;
  set_scale(&a, 5);
  set_scale(&b, 5);
  set_scale(&c, 5);
  set_sign(&a, 1);
  set_sign(&c, 1);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(second_negative_add) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{333, 0, 0, 0}},
              res = DECIMAL_ZERO;
  set_scale(&a, 5);
  set_scale(&b, 5);
  set_scale(&c, 5);
  set_sign(&b, 1);
  set_sign(&c, 1);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST

START_TEST(second_negative_add_1) {
  s21_decimal a = {{555, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{99, 0, 0, 0}},
              res = DECIMAL_ZERO;
  set_scale(&a, 5);
  set_scale(&b, 5);
  set_scale(&c, 5);
  set_sign(&b, 1);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}
END_TEST


Suite *s21_add_suite(void) {
  Suite *suite = suite_create("ADD test");

  TCase *tc_insert = tcase_create("add_test");

  tcase_add_test(tc_insert, add);
  tcase_add_test(tc_insert, first_negative_add);
  tcase_add_test(tc_insert, second_negative_add);
  tcase_add_test(tc_insert, first_negative_add_1);
  tcase_add_test(tc_insert, second_negative_add_1);

  // tcase_add_test(tc_insert, test_01_s21_add);
  // tcase_add_test(tc_insert, test_02_s21_add);
  // tcase_add_test(tc_insert, test_03_s21_add);
  // tcase_add_test(tc_insert, test_04_s21_add);
  // tcase_add_test(tc_insert, test_05_s21_add);
  // tcase_add_test(tc_insert, test_06_s21_add);
  // tcase_add_test(tc_insert, test_07_s21_add);
  // tcase_add_test(tc_insert, test_08_s21_add);
  // tcase_add_test(tc_insert, test_09_s21_add);
  // tcase_add_test(tc_insert, test_10_s21_add);
  // tcase_add_test(tc_insert, test_11_s21_add);
  // tcase_add_test(tc_insert, test_12_s21_add);
  // tcase_add_test(tc_insert, test_13_s21_add);
  // tcase_add_test(tc_insert, test_14_s21_add);
  // tcase_add_test(tc_insert, test_15_s21_add);
  // tcase_add_test(tc_insert, test_16_s21_add);
  // tcase_add_test(tc_insert, test_17_s21_add);
  // tcase_add_test(tc_insert, test_18_s21_add);
  // tcase_add_test(tc_insert, test_19_s21_add);
  // tcase_add_test(tc_insert, test_20_s21_add);
  // tcase_add_test(tc_insert, test_21_s21_add);
  // tcase_add_test(tc_insert, test_22_s21_add);
  // tcase_add_test(tc_insert, test_23_s21_add);
  // tcase_add_test(tc_insert, test_24_s21_add);
  // tcase_add_test(tc_insert, test_25_s21_add);
  // tcase_add_test(tc_insert, test_26_s21_add);
  // tcase_add_test(tc_insert, test_27_s21_add);
  // tcase_add_test(tc_insert, test_28_s21_add);
  // tcase_add_test(tc_insert, test_29_s21_add);
  // tcase_add_test(tc_insert, test_30_s21_add);

  suite_add_tcase(suite, tc_insert);

  return suite;
}
