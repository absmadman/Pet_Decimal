#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int ret_num = 0;
  if (result) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    if (s21_get_bit(*result, 127) == 1) {
      s21_set_bit(result, 127, 0);
    } else {
      s21_set_bit(result, 127, 1);
    }
  } else {
    ret_num = ERROR;
  }
  return ret_num;
}
