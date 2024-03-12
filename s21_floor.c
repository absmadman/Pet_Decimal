#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal zero = {0};

  int shift = s21_get_shift(value);
  int ret_num = 0, sign = s21_get_bit(value, 127);
  if (result) {
    *result = zero;
    if (shift != 0) {
      value.bits[3] = 0;
      if (sign) {
        while_floor(&value, shift);
        s21_add(value, one, &value);
        s21_set_bit(&value, 127, 1);
      } else {
        while_floor(&value, shift);
      }
      *result = value;
    } else {
      *result = value;
    }

  } else {
    ret_num = ERROR;
  }

  return ret_num;
}

void while_floor(s21_decimal *value_1, int shift) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal cup = {0}, zero = {0};
  if (is_zero(*value_1)) {
    *value_1 = zero;
  } else {
    while (shift) {
      div_not_remainder(*value_1, ten, value_1, &cup);
      if (s21_get_shift(*value_1)) {
        *value_1 = zero;
        shift = 1;
      }
      shift--;
    }
  }
}
