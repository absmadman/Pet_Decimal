#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret_num = 0;
  if (result && s21_get_shift(value) < 29) {
    long_decimal long_dec = {0};
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    convert(value, &long_dec);
    for (int i = s21_get_shift(value); i > 0; i -= 1) {
      div_10(&long_dec);
    }
    for (int i = 0; i < 3; i++) {
      result->bits[i] = long_dec.bits[i];
    }
    if (s21_get_bit(value, 127) == 1) {
      result->bits[3] = 1 << 31;
    }
  } else {
    ret_num = ERROR;
  }
  return ret_num;
}
