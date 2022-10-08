#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = OK_STATUS;

  s21_decimal ten = EXP_BASE;

  int sign = get_sign(src);
  int exp = get_exp(&src.bits[3]);

  if (exp >= 0 && exp <= 28) {
    while (exp > 0) {
      s21_div_simple(src, ten, &src);
      exp--;
    }

    if (src.bits[1] || src.bits[2]) {
      res = CONV_ERROR;
      *dst = 0;
    } else {
      *dst = src.bits[0];
      *dst *= (sign) ? -1 : 1;
    }
  } else {
    res = CONV_ERROR;
    *dst = 0;
  }

  return res;
}