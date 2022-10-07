#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_equal(value_1, DECIMAL_ZERO)) {
    return DIV_BY_ZERO;
  }
  s21_div_simple(value_1, value_2, result);

  return OK;
}