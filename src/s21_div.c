#include "s21_decimal.h"

void _head_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               int *exp) {
  int overflow = 0;
  s21_decimal temp = DECIMAL_ONE;
  int min_exp = 0;

  do {
    int i = 0;
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
        s21_add(*result, temp, result);
      }
    }

    min_exp = limit_exp(*result, 0);

    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 ||
        min_exp == 0 || *exp >= 28)
      break;

    if (is_mul_overflow(*result, EXP_BASE))
      break;

    s21_mul(value_1, EXP_BASE, &value_1);
    s21_mul(*result, EXP_BASE, result);

    (*exp)++;
  } while (1);
}

void _make_div_rounding(s21_decimal *value_1, s21_decimal *value_2, int *exp_1,
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

int _align_div_mantises(s21_decimal *value_1, s21_decimal *value_2,
                        s21_decimal *result, int diff, int *exp) {
  int res = OK_STATUS;

  if (!are_mantisses_eq(*value_1, DECIMAL_ZERO)) {
    if (diff < 0) {
      diff = -diff;
      *exp -= diff;

      while (diff != 0) {
        if (is_mul_overflow(*value_1, EXP_BASE)) {
          (*exp)--;
        } else {
          s21_mul(*value_1, EXP_BASE, value_1);
        }
        diff--;
      }
    } else {
      *exp -= diff;

      while (diff != 0) {
        if (is_mul_overflow(*value_2, EXP_BASE)) {
          (*exp)--;
        } else {
          s21_mul(*value_2, EXP_BASE, value_2);
        }
        diff--;
      }
    }
  }

  return res;
}

void _increase_dividend(s21_decimal *value_1, s21_decimal *value_2, int *exp) {
    // TODO: check if max number !!! {
    int additional_exp = 0;
    while (*exp > 0) {
      s21_mul(*value_1, EXP_BASE, value_1);
      s21_mul(*value_2, EXP_BASE, value_2);
      (*exp)--;
    }

    while (is_gr(*value_2, *value_1)) {
      s21_mul(*value_1, EXP_BASE, value_1);
      additional_exp++;
    }
    // }

    *exp += additional_exp;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal divider = value_2;
  int res = OK_STATUS;

  int sign_1 = get_sign(&value_1.bits[3]);
  int sign_2 = get_sign(&value_2.bits[3]);

  int exp_1 = get_exp(&value_1.bits[3]);
  int exp_2 = get_exp(&value_2.bits[3]);

  _make_div_rounding(&value_1, &value_2, &exp_1, &exp_2);

  int diff = exp_1 - exp_2;
  int exp = ((exp_1 > exp_2) ? exp_1 : exp_2);

  res = _align_div_mantises(&value_1, &value_2, result, diff, &exp);
    
  if (are_mantisses_eq(value_2, DECIMAL_ZERO)) {
    res = DIV_BY_ZERO;
    *result = DECIMAL_ZERO;
  } else if (are_mantisses_eq(value_1, DECIMAL_ZERO)) {
    *result = DECIMAL_ZERO;
    exp = 0;
  } else if (are_mantisses_eq(value_2, DECIMAL_MAX) &&
            are_mantisses_eq(value_1, DECIMAL_MAX)) {
    *result = DECIMAL_ONE;
  } else if (are_mantisses_eq(value_2, DECIMAL_MAX)) {
    *result = DECIMAL_ZERO;
    res = SMALL_NUM;
  } else {
    _increase_dividend(&value_1, &value_2, &exp);
    _head_div(value_1, value_2, result, &exp);
  }

  if (res == OK_STATUS) { 
    result->bits[3] |= exp << 16;
    if ((sign_1 && !sign_2) || (!sign_1 && sign_2)) {
      result->bits[3] |= SIGN_DECIMAL_MASK;
    }
  }

  return res;
}
