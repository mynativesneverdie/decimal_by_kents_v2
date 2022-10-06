#include "s21_decimal.h"

int _head_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
              int sign_1, int sign_2) {
  int overflow = 0;
  int res = OK_STATUS;

  for (int i = 0; i < 3; i++) {
    if (overflow) {
      if (value_1.bits[i] > UINT_MAX - 1) {
        overflow = 1;
      } else {
        overflow = 0;
      }
      value_1.bits[i] = bin_add(value_1.bits[i], 1);
    }

    result->bits[i] = bin_add(value_1.bits[i], value_2.bits[i]);

    if ((value_2.bits[i] > UINT_MAX - value_1.bits[i]) && i != 2) {
      if ((i == 1 && value_1.bits[2] == UINT_MAX) ||
          (i == 0 && value_1.bits[1] == UINT_MAX &&
           value_1.bits[2] == UINT_MAX)) {
        if ((!sign_1 && !sign_2) || (sign_1 && sign_2)) {
          max_decimal(result);
          res = LARGE_NUM;
          break;
        }
      }
      overflow = 1;
    }

    if ((value_2.bits[i] > UINT_MAX - value_1.bits[i]) && i == 2) {
      if ((!sign_1 && !sign_2) || (sign_1 && sign_2)) {
        max_decimal(result);
        res = LARGE_NUM;
        break;
      }
    }
  }

  return res;
}

int _align_add_mantises(s21_decimal *value_1, s21_decimal *value_2, int exp_1,
                        int exp_2, int sign_1, int sign_2,
                        s21_decimal *result) {
  int inv = 0;
  int diff = exp_1 - exp_2;

  if (diff < 0) {
    diff = -diff;
    while (diff != 0) {
      s21_mul(*value_1, EXP_BASE, value_1);
      diff--;
    }
  } else {
    while (diff != 0) {
      s21_mul(*value_2, EXP_BASE, value_2);
      diff--;
    }
  }

  if (!sign_1 && sign_2 && is_gr(*value_2, *value_1) ||
      sign_1 && !sign_2 && is_gr(*value_1, *value_2)) {
    result->bits[3] |= SIGN_DECIMAL_MASK;
  } else if (sign_1 && sign_2) {
    result->bits[3] |= SIGN_DECIMAL_MASK;
  }

  if (sign_1 && !sign_2 || !sign_1 && sign_2) {
    if (is_gr(*value_1, *value_2)) {
      if (are_mantisses_eq(*value_1, DECIMAL_MAX)) {
        s21_sub(*value_2, DECIMAL_ONE, value_2);
      } else {
        s21_add(*value_1, DECIMAL_ONE, value_1);
      }

      inv = 0;
    } else {
      inv = 1;
    }

    *value_2 = inv_value(*value_2);
  }

  return inv;
}

void _make_add_rounding(s21_decimal *value_1, s21_decimal *value_2, int sign_1,
                        int sign_2, int *exp_1, int *exp_2) {
  int lim_exp_1 = limit_exp(*value_1, *exp_1);
  int lim_exp_2 = limit_exp(*value_2, *exp_2);

  if ((value_1->bits[2] & FBIT_UINT32_MASK) && *exp_1 > 0 &&
      ((sign_1 && sign_2) || (!sign_1 && !sign_2))) {
    s21_round_tmp(*value_1, value_1);
    (*exp_1)--;
  }

  if ((value_2->bits[2] & FBIT_UINT32_MASK) && *exp_2 > 0 &&
      ((sign_1 && sign_2) || (!sign_1 && !sign_2))) {
    s21_round_tmp(*value_2, value_2);
    (*exp_2)--;
  }

  while (*exp_2 > lim_exp_1 && *exp_2 > *exp_1) {
    s21_round_tmp(*value_2, value_2);
    (*exp_2)--;
  }
  while (*exp_1 > lim_exp_2 && *exp_1 > *exp_2) {
    s21_round_tmp(*value_1, value_1);
    (*exp_1)--;
  }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int inv = 0;
  int overflow = 0;
  int res = OK_STATUS;

  int sign_1 = get_sign(&value_1.bits[3]);
  int sign_2 = get_sign(&value_2.bits[3]);

  int exp_1 = get_exp(&value_1.bits[3]);
  int exp_2 = get_exp(&value_2.bits[3]);

  _make_add_rounding(&value_1, &value_2, sign_1, sign_2, &exp_1, &exp_2);

  inv = _align_add_mantises(&value_1, &value_2, exp_1, exp_2, sign_1, sign_2,
                            result);
  res = _head_add(value_1, value_2, result, sign_1, sign_2);

  result->bits[3] |= ((exp_1 > exp_2) ? exp_1 : exp_2) << 16;
  if (inv) *result = inv_value(*result);

  return res;
}
