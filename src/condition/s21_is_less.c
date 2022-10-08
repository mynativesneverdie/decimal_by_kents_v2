#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int is_less;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int exp1 = get_exp(&value_1.bits[3]);
  int exp2 = get_exp(&value_2.bits[3]);
  
  if (!sign_1 && !sign_2) {
    normalize(&value_1, &value_2);
    is_less = s21_is_less_simple(value_1, value_2);
  } else if (sign_1 ^ sign_2) {
    is_less = (sign_1) ? 1 : 0;
  } else {
    normalize(&value_1, &value_2);
    is_less = !s21_is_less_simple(value_1, value_2);
  }
  if (exp1 > exp2) {
    if (exp1 > value_1.bits[1]) {
      is_less = 1;
    }
  } else if (exp1 < exp2) {
    if (exp2 > value_1.bits[1]) {
      is_less = 0;
    }
  }
  return is_less;
}

