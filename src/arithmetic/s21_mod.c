#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal nul = {0};
  if (s21_is_equal(value_2, nul)) {
    return DIV_BY_ZERO;
  }
  *result = s21_div_simple(value_1, value_2, NULL);

  return OK;
}