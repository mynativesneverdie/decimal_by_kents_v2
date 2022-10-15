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

int is_correct_decimal(s21_decimal value) {
  int ret = 1;

  int exp = get_exp(&value.bits[SCALE]);
  if (exp < 0 || exp > 28) {
    ret = 0;
  }
  for (int i = 96; i < 112; i++) {
    if (get_bit(value, i)) {
      ret = 0;
    }
  }
  for (int i = 120; i < 127; i++) {
    if (get_bit(value, i)) {
      ret = 0;
    }
  }

  return ret;
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

int shift_left(s21_decimal *number) {
  int is_overflow = get_bit(*number, 95);
  for (int i = 95; i >= 0; i--) {
    if (i != 0) {
      set_bit(number, i, get_bit(*number, i - 1));
    } else {
      set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

int shift_right(s21_decimal *number) {
  int is_overflow = get_bit(*number, 1);
  for (int i = 0; i < 96; i++) {
    if (i != 95) {
      set_bit(number, i, get_bit(*number, i + 1));
    } else {
      set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

void set_sign(s21_decimal *number, int sign) {
  if (sign == 0) {
    number->bits[3] = number->bits[3] & ~(1 << 31);
  } else {
    number->bits[3] = number->bits[3] | (1 << 31);
  }
}

int get_scale(s21_decimal number) {
  int shift = 16;
  int scale = 0, i = 0;
  while (shift <= 23) {
    int bit = ((number.bits[3] & (1 << shift)) != 0);
    scale += bit * pow(2, i);
    shift++;
    i++;
  }
  return scale;
}

void set_scale(s21_decimal *number, int scale) {
  int shift = 16;
  while (shift <= 23) {
    if (scale > 0 && scale % 2 == 1) {
      number->bits[3] = number->bits[3] | (1 << shift);
    } else {
      number->bits[3] = number->bits[3] & ~(1 << shift);
    }
    scale /= 2;
    shift++;
  }
}

int get_bit(s21_decimal number, int bit) {
  int sign;
  if ((number.bits[bit / 32] & (1 << bit % 32)) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }
  return sign;
}

void set_bit(s21_decimal *number, int bit, int sign) {
  if (sign == 0) {
    number->bits[bit / 32] = number->bits[bit / 32] & ~(1 << bit % 32);
  } else {
    number->bits[bit / 32] = number->bits[bit / 32] | (1 << bit % 32);
  }
}

void s21_bank_rounding(s21_decimal *value, int count) {
  int system_bit = value->bits[3];
  int exp = get_scale(*value) - count;
  while (count > 0) {
    s21_decimal base = EXP_BASE, one = DECIMAL_ONE, two = {{2, 0, 0, 0}},
                two_res = {0};
    s21_decimal dec_mod = s21_div_simple(*value, base, value);

    if (dec_mod.bits[0] > 5) {
      s21_add_simple(*value, one, value);
    } else if (dec_mod.bits[0] == 5) {
      two_res = s21_div_simple(*value, two, NULL);
      if (s21_is_equal(one, two_res)) {
        s21_add_simple(*value, one, value);
      }
    }
    count--;
  }
  value->bits[3] = system_bit;
  set_scale(value, exp);
}