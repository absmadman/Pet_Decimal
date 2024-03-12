#include "s21_test.h"

START_TEST(from_int_to_decimal_test_1) {
  int res = 0;
  int input = 72;
  s21_decimal dc_res = {0};

  res = s21_from_int_to_decimal(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(72, dc_res.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_2) {
  int res = 0;
  int input = -72;
  s21_decimal dc_res = {0};

  res = s21_from_int_to_decimal(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(72, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

START_TEST(from_int_to_decimal_test_3) {
  int res = 0;
  int input = 72;
  s21_decimal *dc_res = NULL;

  res = s21_from_int_to_decimal(input, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  s = suite_create("s21_from_int_to_decimal_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_from_int_to_decimal_core");
  tcase_add_test(tc_core, from_int_to_decimal_test_1);
  tcase_add_test(tc_core, from_int_to_decimal_test_2);
  tcase_add_test(tc_core, from_int_to_decimal_test_3);

  suite_add_tcase(s, tc_core);

  return s;
}
