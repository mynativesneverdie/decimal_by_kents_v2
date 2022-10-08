#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_DECIMAL 79228162514264337593543950335
#define MIN_DECIMAL -79228162514264337593543950335

#define EXP_DECIMAL_MASK 0xFF0000       // 00000000 11111111 00000000 00000000
#define FULL_EXP_DECIMAL_MASK 0x1C0000  // 00000000 00011100 00000000 00000000
#define SIGN_DECIMAL_MASK 0x80000000    // 10000000 00000000 00000000 00000000
#define LBIT_DECIMAL_MASK 0x000001      // 00000000 00000000 00000000 00000001
#define FBIT_UINT32_MASK 0x80000000     // 10000000 00000000 00000000 00000000
#define DECIMAL_EPS 1e-28

#define BITS_IN_BYTE 32
#define MANTISSA_BYTE_NUM 3

#define START_LOW 0
#define START_MID 32
#define START_HIGH 64
#define START_INFO 96

#define OVERFLOW_FLAG (1U << 0U)

enum errors {
  OK_STATUS = 0,
  OK = 0,
  CALC_ERROR = 1,
  CONV_ERROR = 1,
  LARGE_NUM = 1,
  SMALL_NUM = 2,
  DIV_BY_ZERO = 3
};

enum bits { LOW = 0, MIDDLE = 1, HIGH = 2, SCALE = 3 };

#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

#define DECIMAL_ZERO \
  (s21_decimal) {    \
    { 0, 0, 0, 0 }   \
  }
#define EXP_BASE    \
  (s21_decimal) {   \
    { 10, 0, 0, 0 } \
  }
#define DECIMAL_ONE \
  (s21_decimal) {   \
    { 1, 0, 0, 0 }  \
  }
#define DECIMAL_MAX                     \
  (s21_decimal) {                       \
    { UINT_MAX, UINT_MAX, UINT_MAX, 0 } \
  }

#define OVERFLOW_FLAG (1U << 0U)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Arithmetic functions
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_is_less_simple(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal_simple(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal_simple(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_simple(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal_simple(s21_decimal value_1, s21_decimal value_2);
// void remaind(s21_decimal value_1, s21_decimal value_2, s21_decimal *res);

// Convector functions
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Comparison
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Support functions
int get_exp(unsigned int *bit);
int get_sign(s21_decimal number);
int get_scale(s21_decimal number);
void set_scale(s21_decimal *number, int scale);
int get_bit(s21_decimal number, int bit);
void set_bit(s21_decimal *number, int bit, int sign);
void set_sign(s21_decimal *value, int sign);
int is_correct_decimal(s21_decimal value);
int are_mantisses_eq(s21_decimal value_1, s21_decimal value_2);
unsigned int set_mantissa_byte(int num);
int shift_left(s21_decimal *number);
int shift_right(s21_decimal *number);
void left_float_shift(uint8_t *value);
void right_float_shift(uint8_t *value);
void max_decimal(s21_decimal *value);
void s21_round_tmp(s21_decimal value, s21_decimal *result);
void max_decimal(s21_decimal *value);
int are_mantisses_eq(s21_decimal value_1, s21_decimal value_2);
unsigned int set_mantissa_byte(int num);
int is_gr(s21_decimal value_1, s21_decimal value_2);
long double hreadable_decimal(s21_decimal value);
int limit_exp(s21_decimal value, int exp);
int is_mul_overflow(s21_decimal value_1, s21_decimal value_2);
void initial_val(s21_decimal *value);

// supp funcs for comparison
int get_sign_c(s21_decimal num);
int get_powr(s21_decimal num);
int get_bit_c(s21_decimal num, int curBit);
int switch_res(int result);
int is_zero(s21_decimal value);

// bits operations
s21_decimal inv_value(s21_decimal value);
int get_bit(s21_decimal value, int index);
void set_bit(s21_decimal *value, int index, int v_bit);
int num_bits_in_val(s21_decimal value);
int last_bit(s21_decimal value);
unsigned int bin_add(int a, int b);
unsigned int bin_sub(int a, int b);
unsigned int bin_div(int *a, int b);
unsigned int bin_mul(int a, int b);

// simple arithmetic
int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void s21_sub_simple(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
int s21_mul_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal *result);

void s21_bank_rounding(s21_decimal *value, int count);
void normalize(s21_decimal *value_1, s21_decimal *value_2);
;

#endif  // SRC_S21_DECIMAL_H_
