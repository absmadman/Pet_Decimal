#include "s21_test.h"

START_TEST(from_decimal_to_int_test_1) {
  int res = 0;
  int dc_res = 0;
  s21_decimal dc1 = {{0, 1, 0, 0}};

  res = s21_from_decimal_to_int(dc1, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(from_decimal_to_int_test_2) {
  int res = 0;
  int dc_res = 0;
  s21_decimal dc1 = {{423423, 0, 0, 0}};
  dc1.bits[3] = 1 << 31;

  res = s21_from_decimal_to_int(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(-423423, dc_res);
}
END_TEST

START_TEST(from_decimal_to_int_test_3) {
  int res = 0;
  int dc_res = 0;
  s21_decimal dc1 = {{423423, 0, 0, 0}};
  dc1.bits[3] = 3 << 16 | 0 << 31;

  res = s21_from_decimal_to_int(dc1, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(423, dc_res);
}
END_TEST

START_TEST(from_decimal_to_int_test_4) {
  int res = 0;
  int dc_res = 0;
  s21_decimal dc1 = {{321321313, 3231, 3213, 0}};

  res = s21_from_decimal_to_int(dc1, &dc_res);

  ck_assert_int_eq(1, res);
  // ck_assert_int_eq(423, dc_res);
}
END_TEST

START_TEST(from_decimal_to_int_test_5) {
  int res = 0;
  int *dc_res = NULL;
  s21_decimal dc1 = {{1, 0, 0, 0}};

  res = s21_from_decimal_to_int(dc1, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;
  s = suite_create("s21_from_decimal_to_int_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_from_decimal_to_int_core");
  tcase_add_test(tc_core, from_decimal_to_int_test_1);
  tcase_add_test(tc_core, from_decimal_to_int_test_2);
  tcase_add_test(tc_core, from_decimal_to_int_test_3);
  tcase_add_test(tc_core, from_decimal_to_int_test_4);
  tcase_add_test(tc_core, from_decimal_to_int_test_5);

  suite_add_tcase(s, tc_core);

  return s;
}