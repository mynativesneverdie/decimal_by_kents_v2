#include "../s21_decimal.h"

int count_str_float(float src, char *str_src) {
  int count_str = 0, k = 1;
  char str[100];

  snprintf(str, sizeof(str), "%f", src);

  for (int i = (int)strlen(str) - 1; i >= 0; i--) {
    if (str[i] == '0' && k == 1) {
      str[i] = '\0';
      continue;
    } else {
      k = -1;
    }
    if (str[i] == '.') {
      break;
    }
    count_str++;
  }

  strncpy(str_src, str, strlen(str) + 1);

  return count_str;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  *dst = DECIMAL_ZERO;
  if (fabsf(src) < 1e-28 && fabsf(src) > 0) {
    return CONV_ERROR;
  }

  char str_src[100];
  int count_str = count_str_float(src, str_src), is_overfull = 0;

  s21_decimal ten = EXP_BASE;

  for (size_t i = 0; i < strlen(str_src); i++) {
    if (str_src[i] != '.' && str_src[i] != '-') {
      s21_decimal add;
      s21_from_int_to_decimal(str_src[i] - '0', &add);
      s21_add_simple(*dst, add, dst);
      is_overfull = s21_mul(*dst, ten, dst);
    }
  }

  if (!is_overfull) {
    s21_div_simple(*dst, ten, dst);
  }

  set_sign(dst, src < 0);
  set_scale(dst, count_str);

  return OK;
}