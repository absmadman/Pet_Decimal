#include "s21_test.h"

START_TEST(negate_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);

  res = s21_negate(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1024, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

START_TEST(negate_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc1, 127, 1);

  res = s21_negate(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(64, dc_res.bits[0]);
}
END_TEST

START_TEST(negate_test_3) {
  int res = 0;
  s21_decimal input = {{32397, 0, 0, 0}};
  s21_decimal *dc_res = NULL;

  res = s21_negate(input, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  s = suite_create("s21_negate_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_negate_core");
  tcase_add_test(tc_core, negate_test_1);
  tcase_add_test(tc_core, negate_test_2);
  tcase_add_test(tc_core, negate_test_3);

  suite_add_tcase(s, tc_core);

  return s;
}
