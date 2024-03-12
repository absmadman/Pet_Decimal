#include "s21_decimal.h"

int s21_take_prev(s21_decimal value) {
  int ret = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal float_part = {{0, 0, 0, 0}};
  s21_decimal trunc = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  if (s21_get_shift(value) != 0) {
    if (s21_is_less(value, one) == 1) {
      value.bits[3] = (s21_get_shift(value) - 1) << 16;
      s21_truncate(value, &value);
      ret = value.bits[0];
    } else {
      s21_truncate(value, &trunc);
      s21_sub(value, trunc, &float_part);
      float_part.bits[3] = (s21_get_shift(value) - 1) << 16;
      s21_truncate(float_part, &result);
      ret = result.bits[0];
    }
  }
  return ret;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal zero = {0};
  if (!result) {
    return ERROR;
  }
  if (s21_get_shift(value) == 0) {
    *result = value;
    return 0;
  } else {
    *result = zero;
  }
  s21_decimal one = {{1, 0, 0, 0}};
  int origin_shift = s21_get_shift(value);
  int sign = s21_get_bit(value, 127);
  int curr = 0, prev = 0, flag = 0;
  value.bits[3] = 0;
  for (int i = 1; i <= origin_shift + 1; i += 1) {
    value.bits[3] = i << 16;
    curr = s21_take_prev(value);
    if (i == origin_shift + 1) {
      value.bits[3] = origin_shift << 16;
    }
    if (curr % 2 == 1 && prev == 5) {
      s21_add(value, one, &value);
      value.bits[3] = (s21_get_shift(value) - 1) << 16;
      if (curr == 9) {
        flag = 1;
      }
    } else if (prev > 5) {
      // value.bits[3] = 0 << 16;
      s21_add(value, one, &value);
      if (curr == 9) {
        value.bits[3] = (s21_get_shift(value) - 1) << 16;
        s21_add(value, one, &value);
        flag = 1;
      }
    }
    if (flag == 1) {
      flag = 0;
      s21_sub(value, one, &value);
      curr = 0;
    }
    prev = curr;
  }
  value.bits[3] = origin_shift << 16 | sign << 31;
  s21_truncate(value, result);
  return 0;
}
