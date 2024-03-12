#include "s21_test.h"

START_TEST(from_decimal_to_float_test_1) {
  int res = 0;
  float dc_res = 0;
  s21_decimal dc1 = {{3212, 0, 0, 0}};
  dc1.bits[3] = 1 << 16;

  res = s21_from_decimal_to_float(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_float_eq(321.2, dc_res);
}
END_TEST

START_TEST(from_decimal_to_float_test_2) {
  int res = 0;
  float dc_res = 0;
  s21_decimal dc1 = {{321456, 0, 0, 0}};
  dc1.bits[3] = 3 << 16 | 1 << 31;

  res = s21_from_decimal_to_float(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_float_eq(-321.456, dc_res);
}
END_TEST

START_TEST(from_decimal_to_float_test_3) {
  int res = 0;
  float dc_res = 0;
  s21_decimal dc1 = {{4294967295, 0, 0, 0}};
  dc1.bits[3] = 0 << 16 | 0 << 31;

  res = s21_from_decimal_to_float(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_float_eq(4294967295, dc_res);
}
END_TEST

START_TEST(from_decimal_to_float_test_4) {
  int res = 0;
  s21_decimal dc1 = {{321456, 0, 0, 0}};
  // s21_decimal *null_decimal = NULL;
  float *null_float = NULL;
  res = s21_from_decimal_to_float(dc1, null_float);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s;
  s = suite_create("s21_from_decimal_to_float_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_from_decimal_to_float_core");
  tcase_add_test(tc_core, from_decimal_to_float_test_1);
  tcase_add_test(tc_core, from_decimal_to_float_test_2);
  tcase_add_test(tc_core, from_decimal_to_float_test_3);
  tcase_add_test(tc_core, from_decimal_to_float_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}
