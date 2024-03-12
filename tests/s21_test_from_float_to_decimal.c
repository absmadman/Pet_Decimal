#include <float.h>

#include "s21_test.h"

START_TEST(from_float_to_decimal_test_2) {
  int res = 0;
  float input = -0.72;
  s21_decimal dc_res = {0};

  res = s21_from_float_to_decimal(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(72, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(1, s21_get_bit(dc_res, 113));
}
END_TEST

START_TEST(from_float_to_decimal_test_3) {
  int res = 0;
  s21_decimal dc_res = {0};

  res = s21_from_float_to_decimal(NAN, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(from_float_to_decimal_test_5) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(from_float_to_decimal_test_6) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(from_float_to_decimal_test_7) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(1.02E+09, &result);
  ck_assert_int_eq(result.bits[0], 1020000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(from_float_to_decimal_test_8) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], -2147221504);
}
END_TEST

START_TEST(from_float_to_decimal_test_9) {
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_10) {
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_from_float_to_decimal(-1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_11) {
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_from_float_to_decimal(0.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_12) {
  s21_decimal result = {{0, 0, 0, 0}};
  float a = FLT_MAX;
  int res = s21_from_float_to_decimal(a, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_13) {
  s21_decimal *null_decimal = NULL;
  int res = s21_from_float_to_decimal(5, null_decimal);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_14) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(325325325, &result);
  ck_assert_int_eq(result.bits[0], 325325300);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(from_float_to_decimal_test_15) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(32532133.5321, &result);
  ck_assert_int_eq(result.bits[0], 32532130);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

//
Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  s = suite_create("s21_from_float_to_decimal_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_from_float_to_decimal_core");
  tcase_add_test(tc_core, from_float_to_decimal_test_2);
  tcase_add_test(tc_core, from_float_to_decimal_test_3);
  tcase_add_test(tc_core, from_float_to_decimal_test_5);
  tcase_add_test(tc_core, from_float_to_decimal_test_6);
  tcase_add_test(tc_core, from_float_to_decimal_test_7);
  tcase_add_test(tc_core, from_float_to_decimal_test_8);
  tcase_add_test(tc_core, from_float_to_decimal_test_9);
  tcase_add_test(tc_core, from_float_to_decimal_test_10);
  tcase_add_test(tc_core, from_float_to_decimal_test_11);
  tcase_add_test(tc_core, from_float_to_decimal_test_12);
  tcase_add_test(tc_core, from_float_to_decimal_test_13);
  tcase_add_test(tc_core, from_float_to_decimal_test_14);
  tcase_add_test(tc_core, from_float_to_decimal_test_15);

  suite_add_tcase(s, tc_core);

  return s;
}
