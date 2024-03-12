#include "s21_decimal.h"

int s21_get_shift(s21_decimal src) {
  int shift = (MASK & src.bits[3]) >> 16;
  return shift;
}

void convert(s21_decimal src, long_decimal *dst) {
  for (int i = 0; i < 3; i++) {
    if (src.bits[i] < 0) {
      dst->bits[i] = (~(unsigned int)(-src.bits[i])) + 1;
    } else {
      dst->bits[i] = (unsigned long long int)src.bits[i];
    }
  }
}

void div_10(long_decimal *dst) {
  for (int i = 2; i > 0; i--) {
    dst->bits[i - 1] += (dst->bits[i] % 10) << 32;
  }
  for (int i = 2; i >= 0; i--) {
    dst->bits[i] = dst->bits[i] / 10;
  }
}

int s21_get_bit(s21_decimal dec, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;

  return (dec.bits[num_int] & (1U << num_bit)) >> num_bit;
}

int s21_get_bit_big(s21_big_decimal dec, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;

  return (dec.bits[num_int] & (1U << num_bit)) >> num_bit;
}

int s21_set_bit(s21_decimal *dc, int index, int bit) {
  int flag_err = 0;
  int num_int = index / 32;
  int num_bit = index % 32;

  if (!((index > 95 && index < 112) || (index > 119 && index < 127))) {
    if (bit == 1) {
      dc->bits[num_int] |= 1U << num_bit;
    } else if (bit == 0) {
      dc->bits[num_int] = ~(~dc->bits[num_int] | 1U << num_bit);
    } else {
      flag_err = 1;
    }
  }

  return flag_err;
}

int s21_set_bit_big(s21_big_decimal *dc, int index, int bit) {
  int flag_err = 0;
  int num_int = index / 32;
  int num_bit = index % 32;

  if (bit == 1) {
    dc->bits[num_int] |= 1U << num_bit;
  } else if (bit == 0) {
    dc->bits[num_int] = ~(~dc->bits[num_int] | 1U << num_bit);
  } else {
    flag_err = 1;
  }

  return flag_err;
}

int greater_degree(s21_decimal value_1, s21_decimal value_2) {
  int equal = 0, val_1 = 0, val_2 = 0;
  for (int i = 119; i > 111 && equal == 0; --i) {
    val_1 = s21_get_bit(value_1, i);
    val_2 = s21_get_bit(value_2, i);
    if (val_1 != val_2) {
      if (val_1 > val_2) {
        equal = 1;
      } else {
        equal = 2;
      }
    }
  }
  return equal;
}

void copy_degree(s21_decimal value, s21_decimal *result) {
  for (int i = 119; i > 111; --i) {
    s21_set_bit(result, i, s21_get_bit(value, i));
  }
}

void copy_big_degree(s21_big_decimal value, s21_big_decimal *result) {
  for (int i = 240; i < 255; ++i) {
    s21_set_bit_big(result, i, s21_get_bit_big(value, i));
  }
}

void free_bit(s21_decimal value, int *bit) {
  for (int i = 95; !s21_get_bit(value, i); --i) {
    *bit -= 1;
  }
}

void sub_bits(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal *result) {
  int balance = 0;

  for (int i = 0; i < 32 * 7; ++i) {
    int res1 = s21_get_bit_big(value_1, i);
    int res2 = s21_get_bit_big(value_2, i);

    if (res1 && balance) {
      res1 = 0;
      balance = 0;
    }

    int result_bit = res1 - res2;
    if (result_bit == -1 && !balance) {
      balance = 1;
      result_bit = 1;
    } else if (result_bit == -1 && balance) {
      result_bit = 0;
    } else if (!res1 && !res2 && balance) {
      result_bit = 1;
    }

    s21_set_bit_big(result, i, result_bit);
  }
}

int add_bits(s21_big_decimal val_1, s21_big_decimal val_2,
             s21_big_decimal *result) {
  int flag_return = 0;
  unsigned balance = 0;

  for (int i = 0; i < 32 * 7; ++i) {
    unsigned bit_res =
        s21_get_bit_big(val_1, i) + s21_get_bit_big(val_2, i) + balance;

    balance = bit_res / 2;
    bit_res %= 2;
    s21_set_bit_big(result, i, bit_res);
  }
  flag_return = (check_overflow(*result)) ? 1 : 0;

  return flag_return;
}

void dec_to_big(s21_decimal value, s21_big_decimal *result) {
  s21_big_decimal zero = {0};
  *result = zero;

  for (int i = 0; i < 3; ++i) {
    result->bits[i] = value.bits[i];
  }
  result->bits[7] = value.bits[3];
}

void big_to_dec(s21_big_decimal value, s21_decimal *result) {
  s21_decimal zero = {0};
  *result = zero;

  for (int i = 0; i < 3; ++i) {
    result->bits[i] = value.bits[i];
  }
  result->bits[3] = value.bits[7];
}

int check_sign_big(s21_big_decimal value) {
  int result = 0;
  result = s21_get_bit_big(value, 255);

  return result;
}

int check_sign_dec(s21_decimal value) {
  int result = 0;
  result = s21_get_bit(value, 127);

  return result;
}

int s21_shift_left(s21_big_decimal *res, int num) {
  int flag_return = 0;
  unsigned balance = 0;

  for (int i = 0; i < 7; ++i) {
    unsigned temp = res->bits[i];
    res->bits[i] <<= num;
    res->bits[i] |= balance;
    balance = temp >> (32 - num);
  }
  flag_return = (res->bits[3]) ? 1 : 0;

  return flag_return;
}

int init_big_dec_sub(s21_decimal value_1, s21_decimal value_2,
                     s21_big_decimal *val_1, s21_big_decimal *val_2) {
  int flag_sign = 0;

  s21_set_bit(&value_1, 127, 0);
  s21_set_bit(&value_2, 127, 0);

  if (s21_is_less(value_1, value_2)) {
    dec_to_big(value_2, val_1);
    dec_to_big(value_1, val_2);
    flag_sign = 1;
  } else {
    dec_to_big(value_1, val_1);
    dec_to_big(value_2, val_2);
  }

  return flag_sign;
}

int normalization_degree(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  int flag_return = 0, flag_while = 0;
  s21_big_decimal copy_big_1 = *value_1, copy_big_2 = *value_2;
  int sign_1 = check_sign_big(*value_1);
  int sign_2 = check_sign_big(*value_2);
  int count = 0;

  s21_set_bit_big(&copy_big_1, 255, 0);
  s21_set_bit_big(&copy_big_2, 255, 0);

  while (check_degree_big(copy_big_1) != check_degree_big(copy_big_2) &&
         !flag_return && count != 10) {
    count++;
    flag_while++;
    int deg_1 = check_degree_big(copy_big_1);
    int deg_2 = check_degree_big(copy_big_2);
    s21_big_decimal normal_copy_1 = copy_big_1;
    s21_big_decimal normal_copy_2 = copy_big_2;

    if ((deg_1 > 28) || (normal_degree_up(&normal_copy_2) && deg_1 > 0)) {
      normal_degree_down(&copy_big_1);
    } else if ((deg_2 > 28) ||
               (normal_degree_up(&normal_copy_1) && deg_2 > 0)) {
      normal_degree_down(&copy_big_2);
    } else if (deg_1 < deg_2) {
      normal_degree_up(&copy_big_1);
    } else if (deg_1 > deg_2) {
      normal_degree_up(&copy_big_2);
    } else {
      flag_return = 2;
    }
  }

  if (flag_while) {
    s21_set_bit_big(&copy_big_1, 255, sign_1);
    s21_set_bit_big(&copy_big_2, 255, sign_2);

    *value_1 = copy_big_1;
    *value_2 = copy_big_2;
  }

  return flag_return;
}

void normal_degree_down(s21_big_decimal *value) {
  s21_decimal val_1 = {0}, ten = {0}, remainder = {0}, one = {0},
              degree_value = {0}, zero = {0}, four = {0};
  ten.bits[0] = 10;
  one.bits[0] = 1;
  four.bits[0] = 4;

  big_to_dec(*value, &val_1);
  degree_value.bits[3] = val_1.bits[3];
  val_1.bits[3] = 0;
  ten.bits[3] = val_1.bits[3];
  one.bits[3] = val_1.bits[3];

  if (s21_is_greater_or_equal(val_1, ten)) {
    div_not_remainder(val_1, ten, &val_1, &remainder);
  } else if (s21_is_greater(val_1, four)) {
    remainder = val_1;
    val_1 = zero;
  } else {
    val_1 = zero;
  }
  if (remainder.bits[0] > 5) {
    s21_add(val_1, one, &val_1);
  } else if (remainder.bits[0] == 5 && s21_get_bit(val_1, 0)) {
    s21_add(val_1, one, &val_1);
  } else if (remainder.bits[0] == 5 && !s21_get_bit(val_1, 0)) {
    s21_sub(val_1, one, &val_1);
  }

  val_1.bits[3] = degree_value.bits[3];
  down_degree_dec(&val_1);
  dec_to_big(val_1, value);
}

int normal_degree_up(s21_big_decimal *value) {
  int flag_return = 0;

  s21_decimal copy_value = {0}, save_degree = {0}, one_degree = {0};
  s21_decimal ten = {{0b1010, 0, 0, 0}};
  save_degree.bits[3] = value->bits[7];

  big_to_dec(*value, &copy_value);
  copy_degree(one_degree, &copy_value);
  copy_degree(one_degree, &ten);

  flag_return = s21_mul(copy_value, ten, &copy_value);

  if (!flag_return) {
    dec_to_big(copy_value, value);
    value->bits[7] = save_degree.bits[3];
    up_degree(value);
  }

  return flag_return;
}

int check_degree_big(s21_big_decimal value) {
  int result = (value.bits[7] & 127 << 16) >> 16;

  return result;
}

int check_degree_dec(s21_decimal value) {
  int result = (value.bits[3] & 127 << 16) >> 16;

  return result;
}

void up_degree(s21_big_decimal *value) {
  value->bits[7] = (((value->bits[7] & 127 << 16) >> 16) + 1) << 16;
}

void down_degree_dec(s21_decimal *value) {
  value->bits[3] = (((value->bits[3] & 127 << 16) >> 16) - 1) << 16;
}

int check_free_bits(s21_big_decimal value) {
  int index_offset = 0;
  for (int i = 95; i >= 0 && !index_offset; --i) {
    if (s21_get_bit_big(value, i)) {
      index_offset = i;
    }
  }

  return index_offset;
}

void up_degree_dec(s21_decimal *value) {
  int sign = check_sign_dec(*value);
  s21_set_bit(value, 127, 0);
  value->bits[3] = (((value->bits[3] & 127 << 16) >> 16) + 1) << 16;

  s21_set_bit(value, 127, sign);
}

int check_overflow(s21_big_decimal value) {
  int overflow = 0;

  for (int i = 32 * 7 - 1; i >= 96 && !overflow; --i) {
    if (s21_get_bit_big(value, i)) {
      overflow = 1;
    }
  }

  return overflow;
}

int is_zero(s21_decimal value) {
  int flag_zero = 1;

  for (int i = 95; i >= 0 && flag_zero; --i) {
    if (s21_get_bit(value, i)) {
      flag_zero = 0;
    }
  }

  return flag_zero;
}

int big_is_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int flag_return = 1;

  for (int i = 223; i >= 0 && flag_return; --i) {
    int bit_1 = s21_get_bit_big(value_1, i);
    int bit_2 = s21_get_bit_big(value_2, i);

    if (bit_1 != bit_2) {
      flag_return = 0;
    }
  }

  if (!flag_return) {
    flag_return = big_is_less(value_1, value_2);
  }

  return flag_return;
}

int big_is_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  int flag_end = 0, flag_return = 0;

  for (int i = 223; i >= 0 && !flag_end; --i) {
    int bit_1 = s21_get_bit_big(value_1, i);
    int bit_2 = s21_get_bit_big(value_2, i);

    if (bit_1 != bit_2) {
      if (bit_1 < bit_2) {
        flag_return = 1;
        flag_end = 1;
      } else {
        flag_end = 1;
      }
    }
  }

  return flag_return;
}

int check_degree_overflow(s21_decimal value_1, s21_decimal value_2) {
  int flag_return = 0;

  if (check_degree_dec(value_1) > 28 && check_degree_dec(value_2) > 28) {
    flag_return = 2;
  }

  return flag_return;
}

void down_degree_big(s21_big_decimal *value_1) {
  int degree = value_1->bits[7] >> 16, sign = check_sign_big(*value_1);

  value_1->bits[7] = 0;
  value_1->bits[7] = (degree - 1) << 16;
  s21_set_bit_big(value_1, 255, sign);
}
