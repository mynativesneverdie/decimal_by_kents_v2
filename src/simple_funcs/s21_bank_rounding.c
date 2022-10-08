#include "../s21_decimal.h"

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
