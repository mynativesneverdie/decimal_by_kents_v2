#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int ret = 0;

  if (!is_correct_decimal(value)) {
    ret = CALC_ERROR;
  } else {
    for (int i = 0; i <= MANTISSA_BYTE_NUM; i++) {
      result->bits[i] |= value.bits[i];
      if (value.bits[MANTISSA_BYTE_NUM] & SIGN_DECIMAL_MASK) {
        result->bits[MANTISSA_BYTE_NUM] ^= SIGN_DECIMAL_MASK;
      } else {
        result->bits[MANTISSA_BYTE_NUM] |= SIGN_DECIMAL_MASK;
      }
    }
  }

  return ret;
}
