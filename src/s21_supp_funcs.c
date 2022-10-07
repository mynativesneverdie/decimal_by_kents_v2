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

// void set_sign(s21_decimal *value, int sign) {
//   if (sign == 0) {
//     value->bits[3] = value->bits[3] & ~(1 << 31);
//   } else {
//     value->bits[3] = value->bits[3] | (1 << 31);
//   }
// }

// int get_bit(s21_decimal value, int index) {
//   int ret = (value.bits[index / 32] & (1 << (index % 32))) ? 1 : 0;
//   return ret;
// }

// void set_bit(s21_decimal *value, int index, int v_bit) {
//   if (v_bit == 1) {
//     (value->bits[index / 32] |= (1 << (index % 32)));
//   } else if (v_bit == 0) {
//     (value->bits[index / 32] &= ~(1 << (index % 32)));
//   }
// }

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

// int s21_add_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
//   initial_val(result);
//   int rank = 0;
//   for (int i = 0; i < 96; i++) {
//     int bit_dec1 = get_bit(dec1, i);
//     int bit_dec2 = get_bit(dec2, i);

//     set_bit(result, i, bit_dec1 ^ bit_dec2 ^ rank);

//     rank = (bit_dec1 && bit_dec2) || (bit_dec1 && rank) || (bit_dec2 && rank);
//   }

//   return rank;
// }

// void s21_sub_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
//   initial_val(result);
//   for (int i = 0; i < 96; i++) {
//     int bit_dec1 = get_bit(dec1, i);
//     int bit_dec2 = get_bit(dec2, i);

//     set_bit(result, i, bit_dec1 ^ bit_dec2);

//     if (!bit_dec1 && bit_dec2) {
//       int k = i + 1;
//       while ((bit_dec1 = get_bit(dec1, k)) != 1) {
//         set_bit(&dec1, k, 1);
//         k++;
//       }
//       set_bit(&dec1, k, 0);
//     }
//   }
// }

// s21_decimal s21_div_simple(s21_decimal dec1, s21_decimal dec2,
//                            s21_decimal *result) {
//   if (result) initial_val(result);
//   s21_decimal fmod = {0};
//   s21_decimal temp = {0};
//   if (s21_is_greater_or_equal(dec1, dec2)) set_bit(&temp, 0, 1);
//   if (!s21_is_greater(dec2, dec1)) {
//     while (1) {
//       s21_decimal copy_dec2 = dec2;
//       while (s21_is_greater_or_equal(dec1, copy_dec2) &&
//              !(get_bit(dec1, 95) && get_bit(copy_dec2, 95))) {
//         left_shift(&copy_dec2);
//         left_shift(&temp);
//       }

//       if (!(get_bit(dec1, 95) && get_bit(copy_dec2, 95)) ||
//           (s21_is_greater_or_equal(copy_dec2, dec1))) {
//         right_shift(&copy_dec2);
//         right_shift(&temp);
//       }

//       s21_sub_simple(dec1, copy_dec2, &dec1);
//       if (result) s21_add_simple(*result, temp, result);
//       if (result) initial_val(&temp);

//       set_bit(&temp, 0, 1);
//       if (s21_is_less(dec1, dec2)) {
//         break;
//       }
//     }
//   }
//   fmod = dec1;
//   return fmod;
// }

// void s21_round_tmp(s21_decimal value, s21_decimal *result) {
//   memset(result, 0, sizeof(*result));

//   s21_decimal decimal = EXP_BASE;
//   s21_decimal temp = DECIMAL_ONE;
//   s21_decimal mod = DECIMAL_ZERO;
//   s21_decimal two = {{2, 0, 0, 0}};
//   int overflow = 1;

//   while (!is_gr(decimal, value)) {
//     if ((decimal.bits[2] & FBIT_UINT32_MASK)) {
//       overflow = 1;
//       break;
//     }
//     left_shift(&decimal);
//     left_shift(&temp);
//   }

//   while (is_gr(temp, DECIMAL_ONE)) {
//     if (overflow) {
//       overflow = 0;
//     } else {
//       right_shift(&temp);
//       right_shift(&decimal);
//     }

//     if (!is_gr(decimal, value)) {
//       s21_sub(value, decimal, &value);

//       s21_add(*result, temp, result);
//     }
//   }

//   int reminder = value.bits[0];
//   s21_mod(*result, two, &mod);

//   if (reminder == 5) {
//     if (mod.bits[0] != 0) {
//       s21_add(*result, DECIMAL_ONE, result);
//     }
//   } else if (reminder > 5) {
//     s21_add(*result, DECIMAL_ONE, result);
//   }
// }

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
