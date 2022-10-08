#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int get_exp(unsigned int *bit) {
  int new_bit = (*bit & EXP_DECIMAL_MASK) >> 16;
  *bit &= ~EXP_DECIMAL_MASK;
  return new_bit;
}

int get_sign(s21_decimal number) {
  int sign = 1;

  if ((number.bits[3] & (1 << 31)) == 0) {
    sign = 0;
  }

  return sign;
}

void left_float_shift(uint8_t *value) {
  value[MANTISSA_BYTE_NUM - 1] <<= 1U;

  for (int i = MANTISSA_BYTE_NUM - 2; i >= 0; i--) {
    if (value[i] & 0x80) {
      value[i + 1] |= 1U;
    }
    value[i] <<= 1U;
  }
}

int is_correct_decimal(s21_decimal value) {
  int ret = 1;

  int exp = get_exp(&value.bits[SCALE]);
  if (exp < 0 || exp > 28) {
    ret = 0;
  }
  for (int i = 96; i < 112; i++) {
    if (get_bit(value, i)) ret = 0;
  }
  for (int i = 120; i < 127; i++) {
    if (get_bit(value, i)) ret = 0;
  }

  return ret;
}

int is_zero(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < 96; i++) {
    if (get_bit(value, i) != 0) {
      result = 0;
    }
  }
  return result;
}
