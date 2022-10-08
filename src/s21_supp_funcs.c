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
    s21_decimal base = EXP_BASE, one = DECIMAL_ONE, two = {{2, 0, 0, 0}}, two_res = {0};
    s21_decimal dec_mod = s21_div_simple(*value, base, value);

    if (dec_mod.bits[0] > 5) {
      s21_add_simple(*value, one, value);
    } else if (dec_mod.bits[0] == 5) {
      two_res = s21_div_simple(*value, two, NULL);
      if (s21_is_equal(one, two_res))
        s21_add_simple(*value, one, value);
    }
    count--;
  }
  value->bits[3] = system_bit;
  set_scale(value, exp);
}