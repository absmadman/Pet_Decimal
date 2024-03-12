#ifndef DECIMAL_S21_DECIMAL_H_
#define DECIMAL_S21_DECIMAL_H_
#define DECIMAL_MAX 79228162514264337593543950335.0
#define MASK 127 << 16
#define ERROR 1
#define EQUAL_ZERO_DECIMAL {{0, 0, 0, 0}};

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_big_decimal;

typedef struct {
  unsigned long long int bits[3];
} long_decimal;

int s21_get_shift(s21_decimal src);
int s21_get_shift_big(s21_big_decimal src);
int s21_shift_left(s21_big_decimal *res, int num);
int s21_get_bit(s21_decimal dec, int index);
int s21_get_bit_big(s21_big_decimal dec, int index);
int s21_set_bit(s21_decimal *dc, int index, int bit);
int s21_set_bit_big(s21_big_decimal *dc, int index, int bit);
void up_degree(s21_big_decimal *value);
void down_degree_dec(s21_decimal *value);
void convert(s21_decimal src, long_decimal *dst);
void div_10(long_decimal *dst);

void up_degree_dec(s21_decimal *value);
void update_degree_sub(s21_big_decimal *result, int count_degree);
void copy_degree(s21_decimal value, s21_decimal *result);
void copy_big_degree(s21_big_decimal value, s21_big_decimal *result);
int greater_degree(s21_decimal value_1, s21_decimal value_2);
int normal_degree_up(s21_big_decimal *value);
void normal_degree_down(s21_big_decimal *value);
void normal_degree_for_comparison(s21_decimal *value_1, s21_decimal *value_2);
int check_degree_big(s21_big_decimal value);

int check_degree_dec(s21_decimal value);
int check_degree_overflow(s21_decimal value_1, s21_decimal value_2);
int check_free_bits(s21_big_decimal value);
int check_sign_dec(s21_decimal value);
int check_sign_big(s21_big_decimal value);
int check_overflow(s21_big_decimal value);
int is_zero(s21_decimal value);

void down_degree_for_mull(s21_decimal *result, int *number_degree,
                          int *flag_return);
void add_data_in_zero_result(s21_big_decimal big_val_1,
                             s21_big_decimal big_result, s21_decimal *result);
void big_to_dec(s21_big_decimal value, s21_decimal *result);
void dec_to_big(s21_decimal value, s21_big_decimal *result);
int init_big_dec_sub(s21_decimal value_1, s21_decimal value_2,
                     s21_big_decimal *val_1, s21_big_decimal *val_2);
int normalization_degree(s21_big_decimal *value_1, s21_big_decimal *value_2);
int big_is_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);
int big_is_less(s21_big_decimal value_1, s21_big_decimal value_2);
void search_index(s21_big_decimal big_val_1, s21_big_decimal big_val_2,
                  int *index);
void normal_value_1(s21_big_decimal *big_val_1, s21_big_decimal big_val_2,
                    int *count_degree);
int add_bits(s21_big_decimal val_1, s21_big_decimal val_2,
             s21_big_decimal *result);

void recycle_add_bits(s21_big_decimal big_val_1, s21_big_decimal big_val_2,
                      s21_big_decimal *big_result);
void sub_bits(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal *result);
int mul_bits(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result);
void recycle_mult_bits(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result);
int div_not_remainder(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result, s21_decimal *buff_end);
void normal_values_for_div(s21_decimal *value_1, s21_decimal *value_2);
int div_remainder(s21_decimal buff_end, s21_decimal value_2,
                  s21_decimal *result);
void while_floor(s21_decimal *value_1, int shift);

void print_decimal(s21_decimal value);
void print_big_decimal(s21_big_decimal value);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // DECIMAL_S21_DECIMAL_H_
