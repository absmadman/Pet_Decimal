#include "../s21_decimal.h"

void print_decimal(s21_decimal value) {
  for (int i = 95; i >= 0; --i) {
    printf("%d", s21_get_bit(value, i));
  }
  printf("\n");
}

void print_big_decimal(s21_big_decimal value) {
  for (int i = 95; i >= 0; --i) {
    printf("%d", s21_get_bit_big(value, i));
  }
  printf("\n");
}