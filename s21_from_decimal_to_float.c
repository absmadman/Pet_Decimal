#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  long double result = 0;
  int ret_num = 0;
  if (dst) {
    int shift = s21_get_shift(src);
    for (int i = 0; i < 96; i++) {
      result += s21_get_bit(src, i) * pow(2, i);
    }
    for (int i = 0; i < shift; i++) {
      result /= 10;
    }
    if (s21_get_bit(src, 127) == 1) {
      result = -result;
    }
    *dst = result;
  } else {
    ret_num = ERROR;
  }
  return ret_num;
}
