#include "../s21_decimal.h"

void normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int scl1 = get_scale(*value_1);
  int scl2 = get_scale(*value_2);

  int v1 = value_1->bits[3];
  int v2 = value_2->bits[3];

  int min_scl = (scl1 < scl2) ? scl1 : scl2;
  int max_scl = (scl1 > scl2) ? scl1 : scl2;
  s21_decimal *min_val = (scl1 < scl2) ? value_1 : value_2;
  s21_decimal *max_val = (scl1 > scl2) ? value_1 : value_2;
  s21_decimal ten = EXP_BASE;

  while (min_scl != max_scl) {
    if (min_scl < 28 && !s21_mul_simple(*min_val, ten, min_val)) {
      min_scl++;
      set_scale(min_val, min_scl);
    } else {
      s21_bank_rounding(max_val, max_scl - min_scl);
      break;
    }
  }

  value_1->bits[3] = v1;
  value_2->bits[3] = v2;
  set_scale(min_val, min_scl);
  set_scale(max_val, min_scl);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int is_overfull = OK;

  normalize(&value_1, &value_2);
  int exp = get_scale(value_1);
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  if (!(sign_1 ^ sign_2)) {
    is_overfull = s21_add_simple(value_1, value_2, result);
    set_sign(result, sign_1);

    if (is_overfull && sign_1 && sign_2) {
      is_overfull = SMALL_NUM;
      *result = DECIMAL_ZERO;
    }
  } else if (s21_is_less_or_equal_simple(value_1, value_2)) {
    s21_sub_simple(value_2, value_1, result);
    set_sign(result, sign_2);
  } else {
    s21_sub_simple(value_1, value_2, result);
    set_sign(result, sign_1);
  }

  if (is_overfull && get_scale(value_1)) {
    s21_bank_rounding(&value_1, 1);
    s21_bank_rounding(&value_2, 1);
    is_overfull = s21_add(value_1, value_2, result);
  } else {
    set_scale(result, exp);
  }

  return is_overfull;
}