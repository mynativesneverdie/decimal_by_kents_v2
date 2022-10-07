#include "./s21_decimal.h"

void count_float_nums(float src, int *frac_int_part, int *exp, int *mantiss_num,
                      double *whole_part) {
  float fractional_part = modf(src, whole_part);
  float tmp = *whole_part;

  while (tmp >= 1) {
    tmp /= 10;
    (*mantiss_num)++;
  }

  for (int i = 0;
       i < 7 && ((*mantiss_num) < 29) && (fractional_part * 10 < pow(2, 96));
       i++) {
    fractional_part *= 10;
  }

  if (((int)fractional_part) == 0) {
    *exp = 0;
  } else {
    *exp = 7;
    while ((((int)fractional_part) % 10) == 0) {
      fractional_part /= 10;
      (*exp)--;
    }
  }

  if (*exp == 7) {
    int last_num = ((int)fractional_part) % 10;
    fractional_part /= 10;
    *frac_int_part = (int)fractional_part;
    if (last_num == 5) {
      if (*frac_int_part % 2 != 0) {
        *frac_int_part++;
      }
    } else if (last_num > 5) {
      *frac_int_part++;
    }

    (*exp)--;
  } else {
    *frac_int_part = (int)fractional_part;
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = OK_STATUS;
  *dst = DECIMAL_ZERO;

  if (src < 0) {
    src *= -1;
    dst->bits[3] |= FBIT_UINT32_MASK;
  }

  if (!dst || is_inf(src) || src >= pow(2, 96) || (0 < src && src < 1e-28)) {
    res = CONV_ERROR;
  } else if (src == 0) {
    res = OK_STATUS;
  } else {
    int frac_part = 0, decimal_exp = 0, exp = 0, mantiss_num = 0;
    double whole_part = 0;

    count_float_nums(src, &frac_part, &exp, &mantiss_num, &whole_part);
    float whole = (float)whole_part;

    uint8_t float_num[4];
    memcpy(float_num, &whole, sizeof(whole));
    memcpy(&whole, float_num, sizeof(float_num));

    int float_exp = (float_num[2] & 0x80) ? ((float_num[3] << 1) | 0x01) - 127
                                          : (float_num[3] << 1) - 127;

    if (float_exp > 0) {
      int tmp_float_exp = float_exp;
      left_float_shift(float_num);
      dst->bits[0] = 1;

      while (tmp_float_exp--) {
        shift_left(dst);
        dst->bits[0] |= (float_num[2] & 0x80) ? 1 : 0;
        left_float_shift(float_num);
      }
    }

    for (int i = 0; i < exp; i++) s21_mul(*dst, EXP_BASE, dst);
    dst->bits[0] += frac_part;
    dst->bits[3] |= exp << 16;
  }

  return res;
}
