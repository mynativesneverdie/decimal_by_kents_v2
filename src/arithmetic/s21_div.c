#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;

  if (s21_is_equal(value_2, DECIMAL_ZERO)) {
    res = DIV_BY_ZERO;
    *result = DECIMAL_ZERO;
  } else {
    s21_div_simple(value_1, value_2, result);
  }

  return res;
}