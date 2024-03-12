#include "s21_test.h"

// обычная операция с маленьким числом
START_TEST(sub_test_1) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(960, dc_res.bits[0]);
}
END_TEST

// операция с переносом результата в следующий массив битов
START_TEST(sub_test_2) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 35, 1);
  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 35, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(64, dc_res.bits[0]);
}
END_TEST

// проверка на слишком маленькое число
START_TEST(sub_test_3) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 95, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 95, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

// вычесть большее из меньшего
START_TEST(sub_test_4) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 8, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(192, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

// нормализация степени
START_TEST(sub_test_5) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(64, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
}
END_TEST

START_TEST(sub_test_6) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 95, 1);
  s21_set_bit(&dc2, 95, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(sub_test_7) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 10, 1);
  s21_set_bit(&dc2, 6, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(960, dc_res.bits[0]);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(sub_test_8) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 6, 1);
  s21_set_bit(&dc2, 10, 1);
  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(960, dc_res.bits[0]);
}
END_TEST

START_TEST(sub_test_9) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  s21_set_bit(&dc1, 5, 1);
  s21_set_bit(&dc2, 8, 1);

  dc1.bits[3] = 1900544;
  dc2.bits[3] = 1900544;  // 29

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(sub_test_10) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc1.bits[0] = 3235;
  dc2.bits[0] = 1;

  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc1, 112, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(3245, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
}
END_TEST

START_TEST(sub_test_11) {
  int res = 0;
  s21_decimal dc1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}, dc2 = {0},
              dc_res = {0};

  dc2.bits[0] = 6;

  s21_set_bit(&dc2, 112, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 112));
  ck_assert_int_eq(-2, dc_res.bits[0]);
}
END_TEST

START_TEST(sub_test_12) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc2.bits[0] = 10;

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(10, dc_res.bits[0]);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[2]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
}
END_TEST

START_TEST(sub_test_13) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc2.bits[0] = 10;
  s21_set_bit(&dc2, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(10, dc_res.bits[0]);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[2]);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 127));
}
END_TEST

START_TEST(sub_test_14) {
  int res = 0;
  s21_decimal dc1 = {0}, dc2 = {0}, dc_res = {0};

  dc1.bits[0] = 875;
  dc2.bits[0] = 1;
  s21_set_bit(&dc1, 112, 1);
  s21_set_bit(&dc1, 113, 1);
  s21_set_bit(&dc2, 112, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(775, dc_res.bits[0]);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 112));
  ck_assert_int_eq(1, s21_get_bit(dc_res, 113));
}
END_TEST

START_TEST(sub_test_15) {
  int res = 0;
  s21_decimal dc1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}},
              dc2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}, dc_res = {0};

  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(0, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(0, dc_res.bits[0]);
  ck_assert_int_eq(0, dc_res.bits[1]);
  ck_assert_int_eq(0, dc_res.bits[2]);
}
END_TEST

START_TEST(sub_test_16) {
  int res = 0;
  s21_decimal dc1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}},
              dc2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}, dc_res = {0},
              dc_test = {{0b01100110011001100110011001100101,
                          0b01100110011001100110011001100110,
                          0b11100110011001100110011001100110, 0}};

  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);
  s21_set_bit(&dc_test, 127, 1);

  s21_set_bit(&dc2, 112, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(1, s21_is_equal(dc_res, dc_test));
}
END_TEST

START_TEST(sub_test_17) {
  int res = 0;
  s21_decimal dc1 = {{0b11111111111111111111111111111111, 0b111, 0, 0}},
              dc2 = {{0b11111111111111111111111111111111, 0b111, 0, 0}},
              dc_res = {0},
              dc_templ = {
                  {0b00110011001100110011001100110010, 0b111, 0, 1835008}};

  dc1.bits[3] = 1835008;
  dc2.bits[3] = 1900544;

  s21_set_bit(&dc1, 127, 1);
  s21_set_bit(&dc2, 127, 1);
  s21_set_bit(&dc_templ, 127, 1);

  res = s21_sub(dc1, dc2, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_get_bit(dc_res, 127));
  ck_assert_int_eq(dc1.bits[3], dc_res.bits[3]);

  ck_assert_int_eq(1, s21_is_equal(dc_res, dc_templ));
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s;
  s = suite_create("s21_sub_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_sub_core");
  tcase_add_test(tc_core, sub_test_1);
  tcase_add_test(tc_core, sub_test_2);
  tcase_add_test(tc_core, sub_test_3);
  tcase_add_test(tc_core, sub_test_4);
  tcase_add_test(tc_core, sub_test_5);
  tcase_add_test(tc_core, sub_test_6);
  tcase_add_test(tc_core, sub_test_7);
  tcase_add_test(tc_core, sub_test_8);
  tcase_add_test(tc_core, sub_test_9);
  tcase_add_test(tc_core, sub_test_10);
  tcase_add_test(tc_core, sub_test_11);
  tcase_add_test(tc_core, sub_test_12);
  tcase_add_test(tc_core, sub_test_13);
  tcase_add_test(tc_core, sub_test_14);
  tcase_add_test(tc_core, sub_test_15);
  tcase_add_test(tc_core, sub_test_16);
  tcase_add_test(tc_core, sub_test_17);

  suite_add_tcase(s, tc_core);

  return s;
}