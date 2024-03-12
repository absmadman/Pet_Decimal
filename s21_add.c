#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag_return = 0;
  s21_big_decimal big_val_1 = {0}, big_val_2 = {0}, big_result = {0};
  s21_decimal zero = {0};
  *result = zero;
  flag_return = check_degree_overflow(value_1, value_2);

  if (!flag_return) {
    dec_to_big(value_1, &big_val_1);
    dec_to_big(value_2, &big_val_2);

    normalization_degree(&big_val_1, &big_val_2);

    int sign_1 = check_sign_big(big_val_1);
    int sign_2 = check_sign_big(big_val_2);

    if (sign_1 && !sign_2) {
      s21_set_bit(&value_1, 127, 0);
      flag_return = s21_sub(value_1, value_2, result);
      if (check_sign_dec(*result)) {
        s21_set_bit(result, 127, 0);
      } else {
        s21_set_bit(result, 127, 1);
      }
    } else if (sign_1) {
      recycle_add_bits(big_val_1, big_val_2, &big_result);
      s21_set_bit_big(&big_result, 255, 1);
    } else if (sign_2) {
      s21_set_bit(&value_2, 127, 0);
      flag_return = s21_sub(value_1, value_2, result);
    } else {
      recycle_add_bits(big_val_1, big_val_2, &big_result);
    }

    if (is_zero(*result)) {
      copy_big_degree(big_val_1, &big_result);
      big_to_dec(big_result, result);
      flag_return = (check_overflow(big_result)) ? 1 : 0;
    }
  }

  return flag_return;
}

void recycle_add_bits(s21_big_decimal big_val_1, s21_big_decimal big_val_2,
                      s21_big_decimal *big_result) {
  int flag_return = 0;

  flag_return = add_bits(big_val_1, big_val_2, big_result);

  while (check_degree_big(big_val_1) && check_degree_big(big_val_2) &&
         flag_return) {
    normal_degree_down(&big_val_1);
    normal_degree_down(&big_val_2);
    flag_return = add_bits(big_val_1, big_val_2, big_result);
  }
}
