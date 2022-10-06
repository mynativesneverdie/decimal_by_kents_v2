#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal base = EXP_BASE, mul = DECIMAL_ZERO, one = DECIMAL_ONE;
  s21_truncate(value, result);
  
  int sign = get_sign(&value.bits[3]);
  int exp = get_exp(&value.bits[3]);

  if (exp) exp--;
  while (exp--) {
    s21_div_simple(value, base, &value);
  }
  mul = s21_div_simple(value, base, &value);
  if (mul.bits[0] >= 5) {
    s21_add_simple(*result, DECIMAL_ONE, result);
  }
  set_sign(result, sign);
  return OK;
}
