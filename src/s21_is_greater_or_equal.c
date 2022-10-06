#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  if (s21_is_equal(value_1, value_2) == 1 ||
      s21_is_greater(value_1, value_2) == 1) {
    result = 1;
  }
  return result;
}
