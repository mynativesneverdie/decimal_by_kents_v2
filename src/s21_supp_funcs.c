#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int get_exp(unsigned int *bit) {
  int new_bit = (*bit & EXP_DECIMAL_MASK) >> 16;
  *bit &= ~EXP_DECIMAL_MASK;
  return new_bit;
}

int get_sign(s21_decimal number) {
  int sign = 1;

  if ((number.bits[3] & (1 << 31)) == 0) {
    sign = 0;
  }

  return sign;
}

unsigned int bin_add(int a, int b) {
  int carry;

  while (b != 0) {
    carry = (a & b) << 1;
    a = a ^ b;
    b = carry;
  }

  return a;
}

s21_decimal inv_value(s21_decimal value) {
  s21_decimal temp = {
      {~value.bits[0], ~value.bits[1], ~value.bits[2], value.bits[3]}};
  return temp;
}

int is_gr(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;

  for (int i = 0; i < MANTISSA_BYTE_NUM; i++) {
    if ((value_1.bits[i] || value_2.bits[i]) &&
        (value_1.bits[i] != value_2.bits[i])) {
      res = value_1.bits[i] > value_2.bits[i];
    }
  }

  return res;
}

int are_mantisses_eq(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;

  for (int i = 0; i < 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      res = 0;
      break;
    }
  }

  return res;
}

void left_float_shift(uint8_t *value) {
  value[MANTISSA_BYTE_NUM - 1] <<= 1U;

  for (int i = MANTISSA_BYTE_NUM - 2; i >= 0; i--) {
    if (value[i] & 0x80) {
      value[i + 1] |= 1U;
    }
    value[i] <<= 1U;
  }
}

int limit_exp(s21_decimal value, int exp) {
  int min_exp = 0;

  while (!(value.bits[HIGH] & 0x80000000) && min_exp != 28) {
    value.bits[HIGH] <<= 1U;
    min_exp++;
  }

  return min_exp;
}
int is_mul_overflow(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  int res = 0;

  s21_mul(value_1, value_2, &value_1);
  if (are_mantisses_eq(value_1, max_value)) {
    res = 1;
  }

  return res;
}

void max_decimal(s21_decimal *value) {
  value->bits[0] = UINT_MAX;
  value->bits[1] = UINT_MAX;
  value->bits[2] = UINT_MAX;
}

int is_correct_decimal(s21_decimal value) {
  int ret = 1;

  int exp = get_exp(&value.bits[SCALE]);
  if (exp < 0 || exp > 28) {
    ret = 0;
  }
  for (int i = 96; i < 112; i++) {
    if (get_bit(value, i)) ret = 0;
  }
  for (int i = 120; i < 127; i++) {
    if (get_bit(value, i)) ret = 0;
  }

  return ret;
}

void initial_val(s21_decimal *value) {
  for (int i = 0; i < 128; i++) {
    set_bit(value, i, 0);
  }
}

int get_bit_c(s21_decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }
  return bit;
}

int switch_res(int result) {
  if (result == 0) {
    result = 1;
  } else if (result == 1) {
    result = 0;
  }
  return result;
}

int is_zero(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < 96; i++) {
    if (get_bit(value, i) != 0) {
      result = 0;
    }
  }
  return result;
}
