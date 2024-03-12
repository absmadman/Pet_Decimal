#include "s21_test.h"

// обычная операция с маленьким числом
START_TEST(mul_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(65536, dc_res.bits[0]);
}
END_TEST

// операция с большими числами
START_TEST(mul_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 28, 1);
  s21_set_bit(&dc2, 6, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(4, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[0]);
}
END_TEST

// проверка умножения на ноль
START_TEST(mul_test_3) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, dc_res.bits[0]);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[2]);
}
END_TEST

// работа с отрицательным числом
START_TEST(mul_test_4) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(65536, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

// нормализация степени
START_TEST(mul_test_5) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(65536, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
}
END_TEST

// проверка на слишком большое число
START_TEST(mul_test_6) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 89, 1);
  s21_set_bit(&dc2, 80, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(mul_test_7) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 71, 1);
  s21_set_bit(&dc2, 72, 1);
  s21_set_bit(&dc1, 112, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(mul_test_8) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 6, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(4096, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

START_TEST(mul_test_9) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);

  dc1.bits[3] = 1900544;
  dc2.bits[3] = 1900544;  // 29

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(mul_test_10) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc2, 8, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, dc_res.bits[0]);
}
END_TEST

START_TEST(mul_test_11) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 8, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, dc_res.bits[0]);
}
END_TEST

START_TEST(mul_test_12) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc1.bits[0] = 10;
  dc2.bits[0] = 1;
  s21_set_bit(&dc2, 112, 1);

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(10, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
}
END_TEST

START_TEST(mul_test_13) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc1.bits[0] = 2;
  dc2.bits[0] = 100;
  dc1.bits[3] = 15 << 16;
  dc2.bits[3] = 15 << 16;

  res = s21_mul(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(28, s21_get_shift(dc_res));
  ck_assert_int_eq(2, dc_res.bits[0]);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s;
  s = suite_create("s21_mul_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_mul_core");
  tcase_add_test(tc_core, mul_test_1);
  tcase_add_test(tc_core, mul_test_2);
  tcase_add_test(tc_core, mul_test_3);
  tcase_add_test(tc_core, mul_test_4);
  tcase_add_test(tc_core, mul_test_5);
  tcase_add_test(tc_core, mul_test_6);
  tcase_add_test(tc_core, mul_test_7);
  tcase_add_test(tc_core, mul_test_8);
  tcase_add_test(tc_core, mul_test_9);
  tcase_add_test(tc_core, mul_test_10);
  tcase_add_test(tc_core, mul_test_11);
  tcase_add_test(tc_core, mul_test_12);
  tcase_add_test(tc_core, mul_test_13);

  suite_add_tcase(s, tc_core);

  return s;
}