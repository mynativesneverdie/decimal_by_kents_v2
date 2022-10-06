#include <stdio.h>

#include "s21_decimal.h"

void _head_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal temp = DECIMAL_ONE;
  int overflow = 0;

  while (!is_gr(value_2, value_1)) {
    if ((value_2.bits[2] & FBIT_UINT32_MASK)) {
      overflow = 1;
      break;
    }
    left_shift(&value_2);
    left_shift(&temp);
  }

  while (is_gr(temp, DECIMAL_ONE)) {
    if (overflow) {
      overflow = 0;
    } else {
      right_shift(&temp);
      right_shift(&value_2);
    }

    if (!is_gr(value_2, value_1)) {
      s21_sub(value_1, value_2, &value_1);
    }
  }

  *result = value_1;
}

void _make_mod_rounding(s21_decimal *value_1, s21_decimal *value_2, int *exp_1,
                        int *exp_2) {
  int lim_exp_1 = limit_exp(*value_1, *exp_1);
  int lim_exp_2 = limit_exp(*value_2, *exp_2);

  while (*exp_2 > lim_exp_1 && *exp_2 > *exp_1) {
    s21_round_tmp(*value_2, value_2);
    (*exp_2)--;
  }
  while (*exp_1 > lim_exp_2 && *exp_1 > *exp_2) {
    s21_round_tmp(*value_1, value_1);
    (*exp_1)--;
  }
}

void _align_mod_mantises(s21_decimal *value_1, s21_decimal *value_2, int diff) {
  if (diff < 0) {
    diff = -diff;
    while (diff != 0) {
      if (!is_mul_overflow(*value_1, EXP_BASE)) {
        s21_mul(*value_1, EXP_BASE, value_1);
      }
      diff--;
    }
  } else {
    while (diff != 0) {
      if (!is_mul_overflow(*value_2, EXP_BASE)) {
        s21_mul(*value_2, EXP_BASE, value_2);
      }
      diff--;
    }
  }
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK_STATUS;

  int sign_1 = get_sign(&value_1.bits[3]);
  int sign_2 = get_sign(&value_2.bits[3]);

  int exp_1 = get_exp(&value_1.bits[3]);
  int exp_2 = get_exp(&value_2.bits[3]);

  _make_mod_rounding(&value_1, &value_2, &exp_1, &exp_2);

  int diff = exp_1 - exp_2;
  int exp = ((exp_1 > exp_2) ? exp_1 : exp_2);

  _align_mod_mantises(&value_1, &value_2, diff);

  if (are_mantisses_eq(value_2, DECIMAL_ZERO)) {
    res = DIV_BY_ZERO;
    *result = DECIMAL_ZERO;
  } else if (are_mantisses_eq(value_1, DECIMAL_ZERO)) {
    *result = DECIMAL_ZERO;
  } else if (are_mantisses_eq(value_2, DECIMAL_MAX) &&
             are_mantisses_eq(value_1, DECIMAL_MAX)) {
    *result = DECIMAL_ZERO;
  } else if (are_mantisses_eq(value_2, DECIMAL_MAX)) {
    *result = DECIMAL_ZERO;
    res = SMALL_NUM;
  } else {
    _head_mod(value_1, value_2, result);
  }

  if (res == OK_STATUS) {
    result->bits[3] |= exp << 16;
    if (!(!sign_1 && !sign_2)) {
      result->bits[3] |= SIGN_DECIMAL_MASK;
    }
  }

  return res;
}
