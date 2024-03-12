#include "s21_test.h"

START_TEST(truncate_test_1) {
  int res = 0;
  s21_decimal input = {{3235, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{323, 0, 0, 0}};
  res = s21_truncate(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(truncate_test_2) {
  int res = 0;
  s21_decimal input = {{3213, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 1 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{321, 0, 0, 0}};
  result.bits[3] = 1 << 31;
  res = s21_truncate(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(truncate_test_3) {
  int res = 0;
  s21_decimal input = {{32397, 0, 0, 0}};
  s21_decimal *dc_res = NULL;

  res = s21_truncate(input, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(truncate_test_4) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s;
  s = suite_create("s21_truncate_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_truncate_core");
  tcase_add_test(tc_core, truncate_test_1);
  tcase_add_test(tc_core, truncate_test_2);
  tcase_add_test(tc_core, truncate_test_3);
  tcase_add_test(tc_core, truncate_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}
