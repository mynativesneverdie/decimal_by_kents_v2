#include "s21_decimal.h"
#include <stdio.h>

int _head_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
              int sign_1, int sign_2, int * exp_1, int *exp_2) {
  int res = OK_STATUS;
  int exp = *exp_1 + *exp_2;
  int exit = 0;

  do {
    res = OK_STATUS;
    *result = DECIMAL_ZERO;
    s21_decimal temp_1 = value_1;
    s21_decimal temp_2 = value_2;

    while (!exit) {
      if (temp_2.bits[0] & 1) {
        res = s21_add(*result, temp_1, result);
      }

      right_shift(&temp_2);

      if (left_shift(&temp_1)) {
        max_decimal(result);
        res = LARGE_NUM;
        *result = DECIMAL_MAX;
        if (*exp_1 <= 0 && *exp_2 <= 0) exit = 1;
        break;
      }

      if (are_mantisses_eq(temp_2, DECIMAL_ZERO)) {
        exit = 1;
      }
    }

    if (exp > 0 && !exit) {
      if (*exp_2 > *exp_1) {
        s21_round_tmp(value_2, &value_2);
        (*exp_2)--;
      } else {
        s21_round_tmp(value_1, &value_1);
        (*exp_1)--;
      }
    }
    exp = *exp_1 + *exp_2;

  } while (!exit);

  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = DECIMAL_ZERO;
  int res = OK_STATUS;

  int sign_1 = get_sign(&value_1.bits[3]);
  int sign_2 = get_sign(&value_2.bits[3]);

  int exp_1 = get_exp(&value_1.bits[3]);
  int exp_2 = get_exp(&value_2.bits[3]);

  if (are_mantisses_eq(value_2, DECIMAL_ZERO) ||
      are_mantisses_eq(value_1, DECIMAL_ZERO)) {
    *result = DECIMAL_ZERO;
  } else if (are_mantisses_eq(value_2, DECIMAL_MAX) &&
            is_gr(value_1, DECIMAL_ONE) && 
            (exp_1 == 0 && exp_2 == 0)) {
    res = LARGE_NUM;
    *result = DECIMAL_MAX;
  } else if (are_mantisses_eq(value_1, DECIMAL_MAX) &&
            is_gr(value_2, DECIMAL_ONE) && 
            (exp_1 == 0 && exp_2 == 0)){
    res = LARGE_NUM;
    *result = DECIMAL_MAX;
  } else {    
    res = _head_mul(value_1, value_2, result, sign_1, sign_2, &exp_1, &exp_2);
  }

  int exp = exp_1 + exp_2;

  if (res == OK_STATUS && exp <= 28) {
    result->bits[3] = exp << 16;
  } else if (res == OK_STATUS) {
    *result = DECIMAL_ZERO;
    res = SMALL_NUM;
  }
  
  if ((sign_1 && !sign_2) || (!sign_1 && sign_2)) {
    result->bits[3] |= SIGN_DECIMAL_MASK;
  }

  return res;
}
