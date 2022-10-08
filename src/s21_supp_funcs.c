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

int test_bit(unsigned int value, int BitNumber) {
  return value & (1 << BitNumber);
}

void set_0_bit(unsigned int *value, int BitNumber) {
  *value &= ~(1 << BitNumber);
}

void set_1_bit(unsigned int *value, int BitNumber) {
  *value |= (1 << BitNumber);
}

int exp_float_bin2dec(int bits) {
  int exp_int = 0;
  int index = 30;
  int exp_2 = 7;
  while (index >= 23) {
    if (test_bit(bits, index)) {
      exp_int += pow(2, exp_2);
    }
    index--;
    exp_2--;
  }
  return exp_int;
}

void exp_less_23(int *all_bits_float, int *count_10, int integer_bits,
                 int fractional_bits, s21_decimal *dst, int index_less_0) {
  // flag для нахождения целой части битовой записи и контроля не выхода за
  // диапазон 96 битов для малых чисел
  int flag = 0;
  //память для добавочных разрядов
  //при случае 1 + 1
  //сколько "1" находится в памяти над складываемыми разрядами
  int memory = 0;
  //массив куда пишем результат с конца массива
  int result[NUM_255];
  int bits_copy[NUM_255];
  //индексы массивов для цикла
  int index = 0;
  int j = NUM_255 - 3;
  int ind_help = 0;
  //инициализация
  if (!index_less_0) {
    for (int i = 0; i < NUM_255; i++) {
      result[i] = 2;
      if (i <= 23) {
        bits_copy[i] = all_bits_float[i];
      } else {
        bits_copy[i] = 2;
      }
    }
  } else {
    for (int i = 0; i < NUM_255; i++) {
      bits_copy[i] = all_bits_float[i];
    }
  }
  while (fractional_bits > 0) {
    //инициализация каждый цикл
    index = 0;
    j = NUM_255 - 3;
    for (int i = 0; i < NUM_255; i++) {
      result[i] = 2;
    }
    //нахождение
    for (int k = 0; k < NUM_255; k++) {
      if (bits_copy[k] == 2) {
        index = k - 1;
        break;
      }
    }
    result[NUM_255 - 1] = bits_copy[index];
    result[NUM_255 - 2] = bits_copy[index - 1];
    index -= 2;
    //цикл сложения
    for (; index >= 0; index--, j--) {
      if (bits_copy[index] == 1 && bits_copy[index + 2] == 1) {
        //нет в памяти доп разряда
        if (memory == 0) {
          result[j] = 0;
          memory = 1;
        } else {
          result[j] = 1;
        }
      } else if ((bits_copy[index] == 0 && bits_copy[index + 2] == 1) ||
                 (bits_copy[index] == 1 && bits_copy[index + 2] == 0)) {
        //нет в памяти доп разряда
        if (memory == 0) {
          result[j] = 1;
        } else {
          result[j] = 0;
        }
      } else if (bits_copy[index] == 0 && bits_copy[index + 2] == 0) {
        //нет в памяти доп разряда
        if (memory == 0) {
          result[j] = 0;
        } else {
          result[j] = 1;
          memory = 0;
        }
      }
    }
    //сложение первых двух разрядов
    for (int k = 1; k >= 0; k--, j--) {
      if (bits_copy[k] == 1 && memory == 1) {
        result[j] = 0;
      } else if ((bits_copy[k] == 0 && memory == 1) ||
                 (bits_copy[k] == 1 && memory == 0)) {
        result[j] = 1;
        memory = 0;
      } else if (bits_copy[k] == 0 && memory == 0) {
        result[j] = 0;
      }
    }
    if (memory == 1) {
      result[j] = 1;
      memory = 0;
    }
    for (int k = 254; k >= 0; k--) {
      if (result[k] == 2) {
        ind_help = k + 1;
        integer_bits = 255 - ind_help - fractional_bits + 1;
        break;
      }
    }
    for (int k = 0; ind_help <= 254; ind_help++, k++) {
      bits_copy[k] = result[ind_help];
    }

    flag = 0;
    for (int k = 0, control_index = 0; k < integer_bits; k++) {
      if (bits_copy[k] != 0) flag = 1;
      if (flag) control_index++;
      if (control_index == 95 || control_index + 3 > 95) {
        flag = 2;
        break;
      }
    }
    fractional_bits--;
    *count_10 = *count_10 + 1;
    if (flag == 2) break;
    if (*count_10 == 28) break;
  }
  if (!index_less_0) {
    for (int k = 0; k <= 254; k++) {
      if (bits_copy[k] == 2) {
        index = k - 1;
        break;
      }
    }
  } else {
    for (int k = 0; k < integer_bits; k++) {
      if (bits_copy[k] != 0) {
        for (int q = 0; q < NUM_255 - k - 1; q++) {
          bits_copy[q] = bits_copy[q + k];
        }
        integer_bits -= k;
        break;
      }
    }
    for (int k = 0; k < 96 && k < integer_bits; k++) {
      index = k;
    }
  }
  if (index < 32) {
    write_float_decimal_exp_less(bits_copy, dst, index, 0);
  } else if (32 < index && index < 64) {
    write_float_decimal_exp_less(bits_copy, dst, index, 1);
  } else if (64 < index && index < 96) {
    write_float_decimal_exp_less(bits_copy, dst, index, 2);
  }
}

int exp_more_23(int *all_bits_float, int exp, s21_decimal *dst) {
  int mantis_array[NUM_255];
  int result[NUM_255];
  int exp_2_array[NUM_255];
  int mantis_exp = exp - 23;
  //память для добавочных разрядов
  //при случае 1 + 1
  //сколько "1" находится в памяти над складываемыми разрядами
  int memory = 0;
  //инициализация
  for (int i = 0; i < 23; i++) {
    //заполнение мантисы без первой 1
    mantis_array[i] = all_bits_float[i + 1];
  }
  for (int i = 0; i < NUM_255; i++) {
    result[i] = 2;
    exp_2_array[i] = 2;
    if (i >= 23) {
      mantis_array[i] = 2;
    }
  }
  //начинаем заполнять нулями (сдвигать разряд в мантисе) с 23 индекса
  int index_mantis = 23;
  while (mantis_exp) {
    mantis_array[index_mantis] = 0;
    index_mantis++;
    mantis_exp--;
  }
  // for (int i = index_mantis - 1; i <= index_mantis; i++) {
  //   printf("mantis_array: %d \t index_mantis: %d\n", mantis_array[i], i);
  // }
  //получаем двоичную запись степени 2
  exp_2_array[0] = 1;
  int index_exp_2 = 1;
  while (exp) {
    exp_2_array[index_exp_2] = 0;
    index_exp_2++;
    exp--;
  }
  // for (int i = index_exp_2 - 1; i <= index_exp_2; i++) {
  //   printf("exp_2_array: %d \t index_exp_2: %d\n", exp_2_array[i], i);
  // }
  //складываем двоично exp_2_array и mantis_array
  //перед этим сопоставляем их по последнему элементу
  //последний элемент в mantis_array стоит на месте (index_mantis - 1)
  //последний элемент в exp_2_array стоит на месте (index_exp_2 - 1)
  //сложение записываем в result начиная с 0 индекса и двигаясь
  //поэлементно к 254
  int i = 0;
  while (index_mantis && index_exp_2) {
    if (exp_2_array[index_exp_2 - 1] == 1 &&
        mantis_array[index_mantis - 1] == 1) {
      if (memory) {
        result[i] = 1;
      } else {
        result[i] = 0;
        memory = 1;
      }
    } else if ((exp_2_array[index_exp_2 - 1] == 0 &&
                mantis_array[index_mantis - 1] == 1) ||
               (exp_2_array[index_exp_2 - 1] == 1 &&
                mantis_array[index_mantis - 1] == 0)) {
      if (memory) {
        result[i] = 0;
      } else {
        result[i] = 1;
      }
    } else if (exp_2_array[index_exp_2 - 1] == 0 &&
               mantis_array[index_mantis - 1] == 0) {
      if (memory) {
        result[i] = 1;
        memory = 0;
      } else {
        result[i] = 0;
      }
    }
    index_mantis--;
    index_exp_2--;
    i++;
  }
  if (index_mantis) {
    while (index_mantis) {
      if (mantis_array[index_mantis - 1] == 1 && memory) {
        result[i] = 0;
      } else if (mantis_array[index_mantis - 1] == 0 && memory) {
        result[i] = 1;
        memory = 0;
      } else if (mantis_array[index_mantis - 1] == 1 && !memory) {
        result[i] = 1;
      } else if (mantis_array[index_mantis - 1] == 0 && !memory) {
        result[i] = 0;
      }
      index_mantis--;
      i++;
    }
  } else if (index_exp_2) {
    while (index_exp_2) {
      if (exp_2_array[index_exp_2 - 1] == 1 && memory) {
        result[i] = 0;
      } else if (exp_2_array[index_exp_2 - 1] == 0 && memory) {
        result[i] = 1;
        memory = 0;
      } else if (exp_2_array[index_exp_2 - 1] == 1 && !memory) {
        result[i] = 1;
      } else if (exp_2_array[index_exp_2 - 1] == 0 && !memory) {
        result[i] = 0;
      }
      index_exp_2--;
      i++;
    }
  }
  if (i > 96) {
    return 123;
  }
  i--;
  if (i < 32) {
    write_float_decimal_exp_more(result, dst, i, 0);
  } else if (32 < i && i < 64) {
    write_float_decimal_exp_more(result, dst, i, 1);
  } else if (64 < i && i < 96) {
    write_float_decimal_exp_more(result, dst, i, 2);
  }
  return 0;
}

void exp_less_0(int *all_bits_float, int *count_10, int exp, s21_decimal *dst) {
  int mantis_array[NUM_255];
  exp = -exp;
  mantis_array[0] = 0;
  //заполняем сначала |-exp + 1| нулей, потом пишем 1
  //(2^{-exp}) и пишем остальные 23 нуля + записываем мантису (ее длина 23)
  for (int i = 1; i <= exp + 23; i++) {
    if (i == exp) {
      mantis_array[i] = 1;
    } else if (i > exp) {
      mantis_array[i] = all_bits_float[i - exp];
    } else {
      mantis_array[i] = 0;
    }
  }
  for (int i = 0; i < NUM_255; i++) {
    if (i > exp + 23) {
      mantis_array[i] = 2;
    }
  }
  int integer_bits = 1;
  int fractional_bits = exp + 23;
  exp_less_23(mantis_array, count_10, integer_bits, fractional_bits, dst, 1);
}

void count10_to_bin(int *count_10, int *count_10_bit) {
  int mod_2 = 0;
  int index = 0;
  while (*count_10) {
    mod_2 = *count_10 % 2;
    count_10_bit[index] = mod_2;
    *count_10 /= 2;
    index++;
  }
}

int float_2_bits(float src) { return ((lens_t){.flt = src}).bits; }

int float2decimal_main(int float_bits, int exp, s21_decimal *dst) {
  //счетчик количества умножения на 10
  int count_10 = 0;
  //массив копии битов + 1 от мантисы
  // заполнение от 0 до 23
  int all_bits_float[24] = {0};
  //количество битов целой части
  int integer_bits = exp + 1;
  //количество битов дробной части
  int fractional_bits = 23 - exp;
  // заполняем массив копии битов
  all_bits_float[0] = 1;
  for (int i = 1, index = 22; i <= 23; i++, index--) {
    if (test_bit(float_bits, index)) {
      all_bits_float[i] = 1;
    } else {
      all_bits_float[i] = 0;
    }
  }
  //ошибка для отлавливания чисел > max_decimal
  int error_exp_more_23 = 0;
  //умножаем на 10 пока не выделим целую часть без десятичной дроби
  if (exp < 0) {
    exp_less_0(all_bits_float, &count_10, exp, dst);
  } else if (0 <= exp && exp < 23) {
    exp_less_23(all_bits_float, &count_10, integer_bits, fractional_bits, dst,
                0);
  } else {
    error_exp_more_23 = exp_more_23(all_bits_float, exp, dst);
  }

  //создаем массив в котором будет двоичная запись count_10
  int count_10_bit[8] = {0};
  count10_to_bin(&count_10, count_10_bit);
  for (int i = 0, j = 16; i < 8; i++, j++) {
    if (count_10_bit[i]) {
      set_1_bit(&(dst->bits[3]), j);
    } else {
      set_0_bit(&(dst->bits[3]), j);
    }
  }
  return error_exp_more_23;
}

void write_float_decimal_exp_less(int *bits_copy, s21_decimal *dst, int index,
                                  int bit) {
  int i = 0;
  switch (bit) {
    case 0:
      for (; index >= 0; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[0]), index);
      }
    case 1:
      for (; index >= 32; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[1]), index);
      }
      for (; index >= 0; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[0]), index);
      }
    case 2:
      for (; index >= 64; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[2]), index);
      }
      for (; index >= 32; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[1]), index);
      }
      for (; index >= 0; index--, i++) {
        if (bits_copy[i] == 1) set_1_bit(&(dst->bits[0]), index);
      }
  }
}

void write_float_decimal_exp_more(int *result, s21_decimal *dst, int index,
                                  int bit) {
  switch (bit) {
    case 0:
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
      }
    case 1:
      for (; index >= 32; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[1]), index);
      }
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
      }
    case 2:
      for (; index >= 64; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[2]), index);
      }
      for (; index >= 32; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[1]), index);
      }
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
      }
  }
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

//     rank = (bit_dec1 && bit_dec2) || (bit_dec1 && rank) || (bit_dec2 &&
//     rank);
//   }

//   return rank;
// }

// void s21_sub_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result)
// {
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
