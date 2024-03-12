#include "s21_test.h"

START_TEST(is_greater_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);

  res = s21_is_greater(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(is_greater_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_is_greater(dc1, dc2);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(is_greater_test_3) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_is_greater(dc1, dc2);
  ck_assert_int_eq(0, res);
}
END_TEST

// отрицательное с положительным
START_TEST(is_greater_test_4) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_is_greater(dc1, dc2);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *s21_is_greater_suite(void) {
  Suite *s;
  s = suite_create("s21_is_greater_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_is_greater_core");
  tcase_add_test(tc_core, is_greater_test_1);
  tcase_add_test(tc_core, is_greater_test_2);
  tcase_add_test(tc_core, is_greater_test_3);
  tcase_add_test(tc_core, is_greater_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}