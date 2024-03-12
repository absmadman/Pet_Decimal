#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int ret_num = 0;
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    if (src < 0) {
      s21_set_bit(dst, 127, 1);
      src *= -1;
    }
    dst->bits[0] = src;
  } else {
    ret_num = 1;
  }
  return ret_num;
}