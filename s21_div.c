#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag_return = 0, flag_end = 0;
  s21_decimal buff_end = {0};
  s21_decimal zero = {0};
  *result = zero;

  if (is_zero(value_1)) {
    flag_end = 1;
  }

  flag_return = check_degree_overflow(value_1, value_2);
  flag_return = (is_zero(value_2)) ? 3 : flag_return;
  int sign_1 = check_sign_dec(value_1);
  int sign_2 = check_sign_dec(value_2);
  s21_set_bit(&value_1, 127, 0);
  s21_set_bit(&value_2, 127, 0);

  if (!flag_return && !flag_end) {
    normal_values_for_div(&value_1, &value_2);
    flag_return = (is_zero(value_2)) ? 3 : flag_return;

    if (!flag_return) {
      flag_return = div_not_remainder(value_1, value_2, result, &buff_end);
      copy_degree(buff_end, &zero);

      if (s21_is_not_equal(buff_end, zero)) {
        div_remainder(buff_end, value_2, result);
      }

      if ((sign_1 && !sign_2) || (!sign_1 && sign_2)) {
        s21_set_bit(result, 127, 1);
      }
    }
  }

  return flag_return;
}

void search_index(s21_big_decimal big_val_1, s21_big_decimal big_val_2,
                  int *index) {
  int flag_end = 0;
  s21_big_decimal buff_val = big_val_2;

  for (int i = 0; i < 224 && !flag_end; ++i) {
    if (big_is_less_or_equal(buff_val, big_val_1)) {
      *index = i;
      s21_shift_left(&buff_val, 1);
      continue;
    } else {
      flag_end = 1;
    }
  }
}

int div_not_remainder(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result, s21_decimal *buff_end) {
  int flag_return = 0, index = 0, count_degree = 0;
  s21_big_decimal big_val_1 = {0}, big_val_2 = {0}, big_result = {0};
  s21_decimal zero = {0};
  *buff_end = zero;

  dec_to_big(value_1, &big_val_1);
  dec_to_big(value_2, &big_val_2);

  if (big_is_less(big_val_1, big_val_2)) {
    normal_value_1(&big_val_1, big_val_2, &count_degree);
  }
  do {
    search_index(big_val_1, big_val_2, &index);

    s21_big_decimal buff_val = {{0b1, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < index; ++i) {
      s21_shift_left(&buff_val, 1);
    }
    add_bits(big_result, buff_val, &big_result);

    buff_val = big_val_2;
    for (int i = 0; i < index; ++i) {
      s21_shift_left(&buff_val, 1);
    }
    sub_bits(big_val_1, buff_val, &big_val_1);

  } while (big_is_less_or_equal(big_val_2, big_val_1));

  flag_return = (check_overflow(big_result)) ? 1 : 0;
  if (!flag_return) {
    copy_big_degree(big_val_1, &big_result);
    big_result.bits[7] = 0;
    update_degree_sub(&big_result, count_degree);
    big_to_dec(big_result, result);
    big_to_dec(big_val_1, buff_end);
  }

  return flag_return;
}

void normal_value_1(s21_big_decimal *big_val_1, s21_big_decimal big_val_2,
                    int *count_degree) {
  s21_big_decimal ten = {{0b1010, 0, 0, 0, 0, 0, 0, 0}};
  do {
    *count_degree += 1;
    mul_bits(*big_val_1, ten, big_val_1);
  } while (big_is_less(*big_val_1, big_val_2));
}

void update_degree_sub(s21_big_decimal *result, int count_degree) {
  for (int i = 0; i < count_degree; ++i) {
    up_degree(result);
  }
}

int div_remainder(s21_decimal buff_end, s21_decimal value_2,
                  s21_decimal *result) {
  int count = 0;
  s21_decimal result_div = {0}, ten_dec = {0}, degree_result = {0};
  s21_big_decimal buff_end_big = {0}, big_val_2 = {0}, ten_big = {0};

  degree_result.bits[3] = result->bits[3];
  ten_big.bits[0] = 10;
  ten_dec.bits[0] = 10;

  buff_end.bits[3] = 0;
  value_2.bits[3] = 0;
  result->bits[3] = 0;

  copy_big_degree(big_val_2, &ten_big);
  dec_to_big(value_2, &big_val_2);

  do {
    int count_mull = 0;
    dec_to_big(buff_end, &buff_end_big);

    do {
      count++;
      count_mull++;
      mul_bits(buff_end_big, ten_big, &buff_end_big);

    } while (big_is_less(buff_end_big, big_val_2));
    big_to_dec(buff_end_big, &buff_end);
    div_not_remainder(buff_end, value_2, &result_div, &buff_end);

    for (int i = 0; i < count_mull; ++i) {
      s21_mul(*result, ten_dec, result);
    }
    s21_add(*result, result_div, result);
  } while (!is_zero(buff_end) && count != 7);

  result->bits[3] = degree_result.bits[3];

  for (int i = 0; i < count; ++i) {
    up_degree_dec(result);
  }

  return count;
}

void normal_values_for_div(s21_decimal *value_1, s21_decimal *value_2) {
  s21_big_decimal big_val_1 = {0}, big_val_2 = {0};

  dec_to_big(*value_1, &big_val_1);
  dec_to_big(*value_2, &big_val_2);

  normalization_degree(&big_val_1, &big_val_2);

  big_to_dec(big_val_1, value_1);
  big_to_dec(big_val_2, value_2);
}
