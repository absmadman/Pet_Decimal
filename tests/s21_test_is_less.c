#include "s21_test.h"

START_TEST(is_less_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(is_less_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(is_less_test_3) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(is_less_test_4) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc1, 127, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(is_less_test_5) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  dc1.bits[0] = 1212;
  dc2.bits[0] = 3;

  s21_set_bit(&dc1, 113, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(is_less_test_6) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0};

  s21_set_bit(&dc1, 127, 1);

  res = s21_is_less(dc1, dc2);

  ck_assert_int_eq(0, res);
}
END_TEST

Suite *s21_is_less_suite(void) {
  Suite *s;
  s = suite_create("s21_is_less_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_is_less_core");
  tcase_add_test(tc_core, is_less_test_1);
  tcase_add_test(tc_core, is_less_test_2);
  tcase_add_test(tc_core, is_less_test_3);
  tcase_add_test(tc_core, is_less_test_4);
  tcase_add_test(tc_core, is_less_test_5);
  tcase_add_test(tc_core, is_less_test_6);

  suite_add_tcase(s, tc_core);

  return s;
}