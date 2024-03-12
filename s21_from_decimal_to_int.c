#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ret_num = 0;
  if (dst) {
    if (src.bits[0] != 0) {
      s21_truncate(src, &src);
      if (src.bits[1] || src.bits[2]) {
        *dst = 0;
        ret_num = ERROR;
      } else {
        int number = src.bits[0];
        if (s21_get_bit(src, 127) == 1) {
          number = -number;
        }
        *dst = number;
      }
    } else {
      ret_num = ERROR;
      *dst = 0;
    }
  } else {
    ret_num = ERROR;
  }
  return ret_num;
}
