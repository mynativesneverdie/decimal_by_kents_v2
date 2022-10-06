#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int sign1 = get_sign(&value_1.bits[3]);
  int sign2 = get_sign(&value_2.bits[3]);
  int exp1 = get_exp(&value_1.bits[3]);
  int exp2 = get_exp(&value_2.bits[3]);

  if (exp1 < exp2) {
    result = 0;
  }
  if ((s21_is_equal(value_1, value_2) && exp1 == exp2) || (!sign1 && sign2)) {
    result = 0;
  } else if (sign1 && !sign2) {
      result = 1;
  } else if (sign1 == sign2) {
    for (int i = 95; i >= 0; i--) {
      int bit1 = get_bit_c(value_1, i);
      int bit2 = get_bit_c(value_2, i);

      if (bit1 > bit2) {
        result = 0;
        break;
      } else if (bit2 > bit1) {
        result = 1;
        break;
      }
    }
    if (sign1 && sign2) {
      result = switch_res(result);
    }
  }
  if (exp1 > exp2) {
    if (exp1 > value_1.bits[1]) {
      result = switch_res(result);
    }
  } else if (exp1 < exp2) {
    if (exp2 > value_1.bits[1]) {
      result = 0;
    }
  }
  return result;
}
