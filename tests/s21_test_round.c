#include "s21_test.h"

START_TEST(round_test_1) {
  int res = 0;
  s21_decimal input = {{3235, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  res = s21_round(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_2) {
  int res = 0;
  s21_decimal input = {{3213, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{321, 0, 0, 0}};
  res = s21_round(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST
//
START_TEST(round_test_3) {
  int res = 0;
  s21_decimal input = {{15, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{2, 0, 0, 0}};
  res = s21_round(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_4) {
  int res = 0;
  s21_decimal input = {{3213, 0, 0, 0}};
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{3213, 0, 0, 0}};
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST
//
START_TEST(round_test_5) {
  int res = 0;
  s21_decimal input = {{3235, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 1 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  result.bits[3] = 0 << 16 | 1 << 31;
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_6) {
  int res = 0;
  s21_decimal input = {{3236, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 1 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  result.bits[3] = 0 << 16 | 1 << 31;
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_7) {
  int res = 0;
  s21_decimal input = {{0, 0, 0, 0}};
  //  input.bits[3] = 1 << 16 | 1 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  //  result.bits[3] = 0 << 16 | 0 << 31;
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_8) {
  int res = 0;
  s21_decimal input = {{32395, 0, 0, 0}};
  input.bits[3] = 2 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  result.bits[3] = 0 << 16 | 0 << 31;
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_9) {
  int res = 0;
  s21_decimal input = {{32397, 0, 0, 0}};
  input.bits[3] = 2 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  result.bits[3] = 0 << 16 | 0 << 31;
  res = s21_round(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(round_test_10) {
  int res = 0;
  s21_decimal input = {{32397, 0, 0, 0}};
  input.bits[3] = 2 << 16 | 0 << 31;
  s21_decimal *dc_res = NULL;

  res = s21_round(input, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(round_test_11) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  value_1.bits[3] = 5 << 16;
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_test_12) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  value_1.bits[3] = 5 << 16 | 1 << 31;
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_bit(&check, 127, 1);
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s;
  s = suite_create("s21_round_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_round_core");
  tcase_add_test(tc_core, round_test_1);
  tcase_add_test(tc_core, round_test_2);
  tcase_add_test(tc_core, round_test_3);
  tcase_add_test(tc_core, round_test_4);
  tcase_add_test(tc_core, round_test_5);
  tcase_add_test(tc_core, round_test_6);
  tcase_add_test(tc_core, round_test_7);
  tcase_add_test(tc_core, round_test_8);
  tcase_add_test(tc_core, round_test_9);
  tcase_add_test(tc_core, round_test_10);
  tcase_add_test(tc_core, round_test_11);
  tcase_add_test(tc_core, round_test_12);

  suite_add_tcase(s, tc_core);

  return s;
}
