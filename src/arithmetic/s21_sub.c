#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int is_overfull = OK;
  set_sign(&value_2, !get_sign(value_2));
  is_overfull = s21_add(value_1, value_2, result);

  return is_overfull;
}