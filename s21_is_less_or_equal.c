#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  if (is_zero(value_1) && is_zero(value_2)) {
    result = 1;
  }

  if (s21_get_bit(value_1, 127) > s21_get_bit(value_2, 127) && !result) {
    result = 1;
  }

  if (!result) {
    result = s21_is_equal(value_1, value_2);
  }

  if (!result) {
    result = s21_is_less(value_1, value_2);
  }

  return result;
}