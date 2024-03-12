#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int flag_return = 0;
  int flag_end = 0;

  if (is_zero(value_1) && is_zero(value_2)) {
    flag_return = 0;
    flag_end = 1;
  }

  if (s21_get_bit(value_1, 127) > s21_get_bit(value_2, 127) && !flag_end) {
    flag_return = 1;
    flag_end = 1;
  } else if (s21_get_bit(value_1, 127) < s21_get_bit(value_2, 127) &&
             !flag_end) {
    flag_return = 0;
    flag_end = 1;
  }

  if ((s21_get_shift(value_1) || s21_get_shift(value_2)) && !flag_end) {
    normal_degree_for_comparison(&value_1, &value_2);
  }

  if (!flag_end) {
    int res1 = 0, res2 = 0;

    for (int i = 95; i >= 0 && !flag_end; --i) {
      res1 = s21_get_bit(value_1, i);
      res2 = s21_get_bit(value_2, i);

      if (res1 < res2) {
        flag_return = 1;
        flag_end = 1;
      } else if (res1 > res2) {
        flag_end = 1;
      }
    }
  }

  if (s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127)) {
    flag_return = !flag_return;
  }

  return flag_return;
}
