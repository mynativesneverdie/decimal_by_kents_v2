#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  int sign, exp;

  sign = get_sign(value);
  exp = get_exp(&value.bits[3]);

  if (!is_correct_decimal(value)) {
    ret = CALC_ERROR;
  } else {
    if (exp) {
      s21_decimal base = {0};
      *result = value;
      s21_from_int_to_decimal(10, &base);

      while (exp--) {
        s21_div_simple(*result, base, result);
      }
    } else {
      *result = value;
    }

    if (sign) {
      result->bits[3] |= SIGN_DECIMAL_MASK;
    }
  }

  return ret;
}
