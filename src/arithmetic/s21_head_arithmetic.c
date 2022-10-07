#include "../s21_decimal.h"

int s21_add_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = DECIMAL_ZERO;
  int rank = 0;
  
  for (int i = 0; i < 96; i++) {
    int bit_value_1 = get_bit(value_1, i);
    int bit_value_2 = get_bit(value_2, i);

    set_bit(result, i, bit_value_1 ^ bit_value_2 ^ rank);

    rank = (bit_value_1 && bit_value_2) || (bit_value_1 && rank) || (bit_value_2 && rank);
  }

  return rank;
}

void s21_sub_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = DECIMAL_ZERO;

  for (int i = 0; i < 96; i++) {
    int bit_value_1 = get_bit(value_1, i);
    int bit_value_2 = get_bit(value_2, i);

    set_bit(result, i, bit_value_1 ^ bit_value_2);

    if (!bit_value_1 && bit_value_2) {
      int k = i + 1;
      while ((bit_value_1 = get_bit(value_1, k)) != 1) {
        set_bit(&value_1, k, 1);
        k++;
      }
      set_bit(&value_1, k, 0);
    }
  }
}

int s21_mul_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal tmp = DECIMAL_ZERO;
  *result = DECIMAL_ZERO;

  int is_owerfull = 0;
  for (int i = 0; i < 96 && !is_owerfull; i++) {
    if (get_bit(value_2, i) == 1) {
      s21_decimal temp = value_1;
      int k = 0;
      while (k < i) {
        if (shift_left(&temp)) {
          is_owerfull = 1;
          break;
        }
        k++;
      }
      if (is_owerfull || (is_owerfull = s21_add_simple(temp, tmp, &tmp))) {
        break;
      }
    }
  }

  if (!is_owerfull)
    *result = tmp;

  return is_owerfull;
}

s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal *result) {
  if (result)
    *result = DECIMAL_ZERO;

  s21_decimal fmod = DECIMAL_ZERO;
  s21_decimal temp = DECIMAL_ZERO;

  if (s21_is_greater_or_equal_simple(value_1, value_2))
    set_bit(&temp, 0, 1);
  if (!s21_is_greater_simple(value_2, value_1)) {
    while (1) {
      s21_decimal copy_value_2 = value_2;
      while (s21_is_greater_or_equal_simple(value_1, copy_value_2) &&
             !(get_bit(value_1, 95) && get_bit(copy_value_2, 95))) {
        shift_left(&copy_value_2);
        shift_left(&temp);
      }

      if (!(get_bit(value_1, 95) && get_bit(copy_value_2, 95)) ||
          (s21_is_greater_or_equal_simple(copy_value_2, value_1))) {
        shift_right(&copy_value_2);
        shift_right(&temp);
      }

      s21_sub_simple(value_1, copy_value_2, &value_1);
      if (result)
        s21_add_simple(*result, temp, result);
      temp = DECIMAL_ZERO;
      set_bit(&temp, 0, 1);
      if (s21_is_less_simple(value_1, value_2)) {
        break;
      }
    }
  }
  fmod = value_1;
  return fmod;
}
