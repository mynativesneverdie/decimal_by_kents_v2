#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value);
  s21_truncate(value, result);
  if (sign) s21_add_simple(*result, DECIMAL_ONE, result);
  set_sign(result, sign);
  return OK;
}
