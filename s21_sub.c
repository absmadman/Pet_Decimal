#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {0};
  s21_big_decimal big_val_1 = {0}, big_val_2 = {0}, big_result = {0};
  *result = zero;
  int flag_return = check_degree_overflow(value_1, value_2), flag_sign = 0;
  ;

  if (!flag_return) {
    flag_sign = init_big_dec_sub(value_1, value_2, &big_val_1, &big_val_2);
    flag_return = normalization_degree(&big_val_1, &big_val_2);

    int sign_1 = check_sign_big(big_val_1), sign_2 = check_sign_big(big_val_2);
    int sign_dec_1 = check_sign_dec(value_1),
        sign_dec_2 = check_sign_dec(value_2);

    if (sign_dec_1 && !sign_dec_2) {
      s21_set_bit(&value_1, 127, 0);
      if (s21_add(value_1, value_2, result) == 1) {
        flag_return = 2;
      }
      s21_set_bit(result, 127, 1);
    } else if (!sign_dec_1 && sign_dec_2) {
      s21_set_bit(&value_2, 127, 0);
      if (s21_add(value_1, value_2, result) == 1) {
        flag_return = 2;
      }
    } else if (sign_dec_1 && sign_dec_2) {
      s21_set_bit_big(&big_val_1, 255, 0);
      s21_set_bit_big(&big_val_2, 255, 0);
      sub_bits(big_val_1, big_val_2, &big_result);
      if (s21_is_equal(value_1, value_2)) {
        s21_set_bit_big(&big_result, 255, 0);
      } else if (flag_sign) {
        s21_set_bit_big(&big_result, 255, 0);
      } else {
        s21_set_bit_big(&big_result, 255, 1);
      }
    } else {
      if (s21_is_less(value_1, value_2) && !sign_1 && !sign_2) {
        s21_set_bit_big(&big_result, 255, 1);
      }
      sub_bits(big_val_1, big_val_2, &big_result);
    }
    flag_return =
        (!flag_return && check_overflow(big_result)) ? 2 : flag_return;
    add_data_in_zero_result(big_val_1, big_result, result);
  }

  return flag_return;
}

void add_data_in_zero_result(s21_big_decimal big_val_1,
                             s21_big_decimal big_result, s21_decimal *result) {
  if (is_zero(*result)) {
    copy_big_degree(big_val_1, &big_result);
    big_to_dec(big_result, result);
  }
}
