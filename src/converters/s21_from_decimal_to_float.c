#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ret = 0;

  if (!is_correct_decimal(src)) {
    ret = 1;
    *dst = 0.0;
  } else {
    *dst = 0.0;
    double tmp = 0.00000000;
    int sign = get_sign(src);
    int exp = get_exp(&src.bits[3]);

    for (int i = 0; i < 96; i++) {
      tmp += (get_bit(src, i) * pow(2.0, i));
    }

    double power_of_new_number = pow(10, exp);
    tmp /= power_of_new_number;

    if (sign) {
      tmp *= -1.0;
    }

    *dst = (float)tmp;
  }

  return ret;
}
