#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int sign1 = get_sign(&value_1.bits[3]);
  int sign2 = get_sign(&value_2.bits[3]);
  int pow1 = get_exp(&value_1.bits[3]);
  int pow2 = get_exp(&value_2.bits[3]);

  if (sign1 == sign2 && pow1 == pow2) {
    for (int i = 0; i < 3; i++) {
      if (value_1.bits[i] != value_2.bits[i]) {
        result = 0;
        break;
      }
    }
  } else {
    result = 0;
  }
  return result;
}
