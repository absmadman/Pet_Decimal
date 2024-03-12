#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag_return = 0, value_zero = 0, number_degree = 0;
  s21_big_decimal big_val_1 = {0}, big_val_2 = {0}, big_result = {0};
  s21_decimal zero = {0};
  *result = zero;

  if (is_zero(value_1) || is_zero(value_2)) {
    value_zero = 1;
  }

  flag_return = check_degree_overflow(value_1, value_2);

  if (!flag_return && !value_zero) {
    number_degree = s21_get_shift(value_1) + s21_get_shift(value_2);

    dec_to_big(value_1, &big_val_1);
    dec_to_big(value_2, &big_val_2);

    int sign_1 = check_sign_big(big_val_1);
    int sign_2 = check_sign_big(big_val_2);

    recycle_mult_bits(big_val_1, big_val_2, &big_result);
    copy_big_degree(big_val_1, &big_result);

    flag_return = (check_overflow(big_result)) ? 1 : flag_return;

    if (!flag_return) {
      big_to_dec(big_result, result);
      down_degree_for_mull(result, &number_degree, &flag_return);
      result->bits[3] = number_degree << 16;
    }

    if ((sign_1 && !sign_2) || (!sign_1 && sign_2)) {
      s21_set_bit(result, 127, 1);
      flag_return = (flag_return) ? 2 : flag_return;
    }
  }
  return flag_return;
}

int mul_bits(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result) {
  int index = check_free_bits(value_2), flag_return = 0;
  s21_big_decimal copy_val_1 = {0}, copy_res = {0}, zero = {0};
  *result = zero;

  for (int i = index; i >= 0; --i) {
    if (s21_get_bit_big(value_2, i)) {
      copy_val_1 = value_1;
      copy_res = *result;
      add_bits(copy_res, copy_val_1, result);
    }

    if (i != 0) {
      s21_shift_left(result, 1);
    }
  }

  flag_return = (check_overflow(*result)) ? 1 : 0;

  return flag_return;
}

void recycle_mult_bits(s21_big_decimal big_val_1, s21_big_decimal big_val_2,
                       s21_big_decimal *big_result) {
  int flag_return = 0;

  flag_return = mul_bits(big_val_1, big_val_2, big_result);

  while (check_degree_big(big_val_1) && check_degree_big(big_val_2) &&
         flag_return) {
    normal_degree_down(&big_val_1);
    normal_degree_down(&big_val_2);
    flag_return = mul_bits(big_val_1, big_val_2, big_result);
  }
}

void down_degree_for_mull(s21_decimal *result, int *number_degree,
                          int *flag_return) {
  s21_decimal zero = {0}, ten = {0};
  int flag_end = 0;
  ten.bits[0] = 10;

  result->bits[3] = 0;
  while (*number_degree > 28 && !*flag_return && !flag_end) {
    if (s21_is_less(*result, ten)) {
      *result = zero;
      flag_end = 1;
    } else {
      *flag_return = s21_div(*result, ten, result);
    }
    *number_degree -= 1;
  }
}
