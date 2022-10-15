#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_equal;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  s21_decimal nul;
  s21_from_int_to_decimal(0, &nul);

  if (sign_1 ^ sign_2) {
    is_equal = 0;
    if (s21_is_equal_simple(value_1, nul) &&
        s21_is_equal_simple(value_2, nul)) {
      is_equal = 1;
    }
  } else {
    normalize(&value_1, &value_2);
    is_equal = s21_is_equal_simple(value_1, value_2);
  }
  return is_equal;
}
