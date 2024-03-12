#include "s21_test.h"

// обычная операция с маленьким числом
START_TEST(add_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 10, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1088, dc_res.bits[0]);
}
END_TEST

// операция с переносом результата в следующий массив битов
START_TEST(add_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 31, 1);
  s21_set_bit(&dc2, 31, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[0]);
}
END_TEST

// второе отрицательное число
START_TEST(add_test_3) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 31, 1);
  s21_set_bit(&dc2, 31, 1);
  s21_set_bit(&dc1, 127, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[0]);
}
END_TEST

// оба отрицательных числа
START_TEST(add_test_4) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 31, 1);
  s21_set_bit(&dc2, 31, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

// первое число отрицательное и его модуль меньше второго
START_TEST(add_test_5) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc1, 127, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(960, dc_res.bits[0]);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 127));
}
END_TEST

// проверка на слишком большое число
START_TEST(add_test_6) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 95, 1);
  s21_set_bit(&dc2, 95, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

// работа с большим отрицательным числом
START_TEST(add_test_7) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 8, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(192, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

// нормализация степени
START_TEST(add_test_8) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(576, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
}
END_TEST

START_TEST(add_test_9) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);
  dc1.bits[3] = 1900544;  // 29 степень
  dc2.bits[3] = 1835008;  // 28

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(259, dc_res.bits[0]);
  ck_assert_int_eq(1835008, dc_res.bits[3]);
}
END_TEST

START_TEST(add_test_10) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 94, 1);
  s21_set_bit(&dc2, 94, 1);
  s21_set_bit(&dc2, 95, 1);
  s21_set_bit(&dc1, 112, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(add_test_11) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 94, 1);
  s21_set_bit(&dc2, 94, 1);
  s21_set_bit(&dc2, 95, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(add_test_12) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);
  dc1.bits[3] = 1900544;  // 29
  dc2.bits[3] = 1966080;

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(add_test_13) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);  // 32
  s21_set_bit(&dc2, 8, 1);  // 256

  dc1.bits[3] = 1835008;  // 28
  dc2.bits[3] = 1900544;  // 29

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(58, dc_res.bits[0]);
  ck_assert_int_eq(1835008, dc_res.bits[3]);
}
END_TEST

START_TEST(add_test_14) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);

  dc1.bits[3] = 1900544;
  dc2.bits[3] = 1900544;  // 29

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(add_test_15) {
  int res = 0;
  s21_decimal dc1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal dc2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal dc_res = {0};

  s21_set_bit(&dc1, 127, 1);

  s21_set_bit(&dc1, 112, 1);

  s21_set_bit(&dc2, 112, 1);
  s21_set_bit(&dc1, 113, 1);

  res = s21_add(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s;
  s = suite_create("s21_add_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_add_core");
  tcase_add_test(tc_core, add_test_1);
  tcase_add_test(tc_core, add_test_2);
  tcase_add_test(tc_core, add_test_3);
  tcase_add_test(tc_core, add_test_4);
  tcase_add_test(tc_core, add_test_5);
  tcase_add_test(tc_core, add_test_6);
  tcase_add_test(tc_core, add_test_7);
  tcase_add_test(tc_core, add_test_8);
  tcase_add_test(tc_core, add_test_9);
  tcase_add_test(tc_core, add_test_10);
  tcase_add_test(tc_core, add_test_11);
  tcase_add_test(tc_core, add_test_12);
  tcase_add_test(tc_core, add_test_13);
  tcase_add_test(tc_core, add_test_14);
  tcase_add_test(tc_core, add_test_15);

  suite_add_tcase(s, tc_core);

  return s;
}