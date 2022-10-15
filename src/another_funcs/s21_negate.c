#include "../s21_decimal.h"

int s21_negate(s21_decimal value_1, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else if (!is_correct_decimal(value_1)) {
    ret = 1;
  } else {
    *result = value_1;
    int sign = get_sign(value_1);

    if (sign)
      sign = 0;
    else
      sign = 1;

    set_sign(result, sign);
  }
  return ret;
}
