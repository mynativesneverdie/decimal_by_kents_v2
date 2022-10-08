#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = OK_STATUS;
  *dst = DECIMAL_ZERO;

  if (src < 0) {
    src *= -1;
    dst->bits[3] |= SIGN_DECIMAL_MASK;
  }

  dst->bits[0] = src;

  return res;
}
