#ifndef C5_S21_DECIMAL_1_S21_TEST_H_
#define C5_S21_DECIMAL_1_S21_TEST_H_

#include <check.h>

#include "../s21_decimal.h"

#define OK 0
#define BIG 1
#define SMALL 2
#define DIV_NULL 3

Suite* s21_add_suite(void);
Suite* s21_div_suite(void);
Suite* s21_is_equal_suite(void);
Suite* s21_is_greater_suite(void);
Suite* s21_is_greater_or_equal_suite(void);
Suite* s21_is_less_suite(void);
Suite* s21_is_less_or_equal_suite(void);
Suite* s21_is_not_equal_suite(void);
Suite* s21_mul_suite(void);
Suite* s21_sub_suite(void);
Suite* s21_negate_suite(void);
Suite* s21_from_decimal_to_float_suite(void);
Suite* s21_from_decimal_to_int_suite(void);
Suite* s21_from_int_to_decimal_suite(void);
Suite* s21_from_float_to_decimal_suite(void);
Suite* s21_round_suite(void);
Suite* s21_floor_suite(void);
Suite* s21_truncate_suite(void);
Suite* s21_is_greater_copy_suite(void);
#endif  // C5_S21_DECIMAL_1_S21_TEST_H_
