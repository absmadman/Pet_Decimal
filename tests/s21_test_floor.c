#include "s21_test.h"

#define TRUE 1
#define FALSE 0

START_TEST(floor_test_1) {
  int res = 0;
  s21_decimal input = {{3235, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{323, 0, 0, 0}};
  res = s21_floor(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(floor_test_2) {
  int res = 0;
  s21_decimal input = {{3213, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 0 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{321, 0, 0, 0}};
  res = s21_floor(input, &dc_res);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(floor_test_3) {
  int res = 0;
  s21_decimal input = {{3235, 0, 0, 0}};
  input.bits[3] = 1 << 16 | 1 << 31;
  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{324, 0, 0, 0}};
  result.bits[3] = 0 << 16 | 1 << 31;
  res = s21_floor(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(floor_test_4) {
  int res = 0;
  s21_decimal input = {{323, 0, 0, 0}};

  s21_decimal dc_res = {{0, 0, 0, 0}};
  s21_decimal result = {{323, 0, 0, 0}};

  res = s21_floor(input, &dc_res);

  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, s21_is_equal(dc_res, result));
}
END_TEST

START_TEST(floor_test_5) {
  int res = 0;
  s21_decimal input = {{323, 0, 0, 0}};

  s21_decimal *dc_res = NULL;

  res = s21_floor(input, dc_res);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(floor_test_1_) {
  s21_decimal values_1[] = {
      {{0x2B3100BE, 0x00000002, 0x00000000, 0x00000000}},  // 9314566334
      {{0x000E3680, 0x00000000, 0x00000000, 0x00030000}},  // 931.456
      {{0x0011A1E3, 0x00000000, 0x00000000, 0x00000000}},  // 1155555
      {{0x99362457, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712727
      {{0x3E8700BA, 0x00000001, 0x00000000, 0x80040000}},  //-534400.2234
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
      {{0x944C4020, 0x0003328B, 0x00000000, 0x80020000}},  //-9000000000000.32
      {{0x0137EBBA, 0x00000000, 0x00000000, 0x00050000}},  // 204.42042
      {{0xAFA09019, 0x0002CD6B, 0x00000000, 0x80070000}},  //-78881234.5151513
      {{0xAE1DD5F5, 0xD24B7E6A, 0x00000000,
        0x00080000}},  // 151533443678.70989813
      {{0x37BFBC9E, 0x1BCECFDE, 0x0000D3C2,
        0x80020000}},  //-10000000000032323445546.54
      {{0x50EF6808, 0x0013B381, 0x00000000, 0x00000000}},  // 5545392547522568
      {{0x540BE3FF, 0x00000002, 0x00000000, 0x80030000}},  //-9999999.999
      {{0x00BBB0A8, 0x00000000, 0x00000000, 0x80020000}},  //-123004.56
      {{0x000000F4, 0x00000000, 0x00000000, 0x00030000}},  // 0.244
      {{0x0000000F, 0x00000014, 0x0000072E, 0x800A0000}},
      //                                              -3390511560756.4055216143
      {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x80050000}},
      //                                                  -184467440737095.51615
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
      //                                           79228162514264337593543950335

      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      //                                          -79228162514264337593543950335
      {{0x05288CC2, 0x00000000, 0x00000000, 0x00030000}},  // 86543.554
      {{0x05288CC2, 0x00000000, 0x00000000, 0x80030000}},  //-86543.554
      {{0x0165D6E5, 0x00000000, 0x00000000, 0x00040000}},  // 2345.1365
      {{0x0165D6E5, 0x00000000, 0x00000000, 0x80040000}},  //-2345.1365
      {{0xE76A2483, 0x00011DB9, 0x00000000, 0x000E0000}},  // 3.14159265358979
      {{0xE76A2483, 0x00011DB9, 0x00000000, 0x800E0000}},  //-3.14159265358979
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
      {{0x00000000, 0x00000000, 0x00000000, 0x00030000}},  // 0.000
      {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // 0.5
      {{0x00000005, 0x00000000, 0x00000000, 0x80010000}}   //-0.5
  };
  s21_decimal values_2[] = {
      {{0x2B3100BE, 0x00000002, 0x00000000, 0x00000000}},  // 9314566334
      {{0x000003A3, 0x00000000, 0x00000000, 0x00000000}},  // 931
      {{0x0011A1E3, 0x00000000, 0x00000000, 0x00000000}},  // 1155555
      {{0x0149EB75, 0x00000000, 0x00000000, 0x00000000}},  // 21621621
      {{0x00082781, 0x00000000, 0x00000000, 0x80000000}},  //-534401
      {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
      {{0x79CD9001, 0x0000082F, 0x00000000, 0x80000000}},  //-9000000000001
      {{0x000000CC, 0x00000000, 0x00000000, 0x00000000}},  // 204
      {{0x04B3A1D3, 0x00000000, 0x00000000, 0x80000000}},  //-78881235
      {{0x4818DA5E, 0x00000023, 0x00000000, 0x00000000}},  // 151533443678
      {{0x38E0A32B, 0x19E0C9C2, 0x0000021E,
        0x80000000}},  //-10000000000032323445547
      {{0x50EF6808, 0x0013B381, 0x00000000, 0x00000000}},  // 5545392547522568
      {{0x00989680, 0x00000000, 0x00000000, 0x80000000}},  //-10000000
      {{0x0001E07D, 0x00000000, 0x00000000, 0x80000000}},  //-123005
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
      {{0x6A3CB835, 0x00000315, 0x00000000, 0x80000000}},
      //                                              -3390511560757
      {{0xAC471B48, 0x0000A7C5, 0x00000000, 0x80000000}},
      //                                                  -184467440737096
      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
      //                                           79228162514264337593543950335

      {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
      //                                          -79228162514264337593543950335
      {{0x0001520F, 0x00000000, 0x00000000, 0x00000000}},  // 86543
      {{0x00015210, 0x00000000, 0x00000000, 0x80000000}},  //-86544
      {{0x00000929, 0x00000000, 0x00000000, 0x00000000}},  // 2345
      {{0x0000092A, 0x00000000, 0x00000000, 0x80000000}},  //-2346
      {{0x00000003, 0x00000000, 0x00000000, 0x00000000}},  // 3
      {{0x00000004, 0x00000000, 0x00000000, 0x80000000}},  //-4
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
      {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
      {{0x00000001, 0x00000000, 0x00000000, 0x80000000}}   //-1
  };
  for (size_t i = 0; i < sizeof(values_1) / sizeof(s21_decimal); i++) {
    s21_decimal res = {0};
    int ret = s21_floor(values_1[i], &res);
    ck_assert_int_eq(TRUE, s21_is_equal(res, values_2[i]));
    ck_assert_int_eq(ret, FALSE);
  }
}
END_TEST

START_TEST(floor_test_2_) {
  s21_decimal error_value_1 = {
      {0x0000000A, 0x0000000D, 0x0000033B, 0x001E0000}};
  s21_decimal error_value_2;
  int ret = s21_truncate(error_value_1, &error_value_2);
  ck_assert_int_eq(ret, TRUE);
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s;
  s = suite_create("s21_floor_suite");

  TCase *tc_core;
  tc_core = tcase_create("s21_floor_core");
  tcase_add_test(tc_core, floor_test_1);
  tcase_add_test(tc_core, floor_test_2);
  tcase_add_test(tc_core, floor_test_3);
  tcase_add_test(tc_core, floor_test_4);
  tcase_add_test(tc_core, floor_test_5);
  tcase_add_test(tc_core, floor_test_1_);
  tcase_add_test(tc_core, floor_test_2_);

  suite_add_tcase(s, tc_core);

  return s;
}