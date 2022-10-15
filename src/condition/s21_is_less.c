#include "../s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = false;
  if (is_zero(a) && is_zero(b)) return res;

  if (get_sign(a) != get_sign(b)) {
    res = get_sign(a);
  } else {
    normalize(&a, &b);
    res = s21_is_less_simple(a, b);
    if (get_sign(a)) res ^= 1;
  }

  return res;
}
