#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  if (s21_get_bit(value_1, 127) != s21_get_bit(value_2, 127)) {
    result = 0;
  }

  if (result) {
    for (int i = 0; i < 128 && result; ++i) {
      int check_value_1 = s21_get_bit(value_1, i);
      int check_value_2 = s21_get_bit(value_2, i);

      if (check_value_1 != check_value_2) {
        result = 0;
      }
    }
  }

  return result;
}