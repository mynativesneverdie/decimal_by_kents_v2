#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign = get_sign(&value_2.bits[3]);
  int res = OK_STATUS;

  if (!sign) {
    value_2.bits[3] |= SIGN_DECIMAL_MASK;
  }

  res = s21_add(value_1, value_2, result);
  return res;
}
