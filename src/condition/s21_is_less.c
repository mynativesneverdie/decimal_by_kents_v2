#include "../s21_decimal.h"

int stupid_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = 96 - 1; i >= 0; i--) {
    if (get_bit(value_1, i) == get_bit(value_2, i))
      continue;
    else if (get_bit(value_1, i) < get_bit(value_2, i))
      res = 1;
    break;
  }
  return res;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = false;
  if (is_zero(a) && is_zero(b)) return res;

  if (get_sign(a) != get_sign(b)) {
    res = get_sign(a);
  } else {
    normalize(&a, &b);
    res = stupid_less(a, b);
    if (get_sign(a)) res ^= 1;
  }

  return res;
}

