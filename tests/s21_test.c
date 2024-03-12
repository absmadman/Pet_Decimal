#include "s21_test.h"

int main() {
  int failed = 0;
  Suite *s21_string_test[] = {s21_add_suite(),
                              s21_div_suite(),
                              s21_is_equal_suite(),
                              s21_is_greater_suite(),
                              s21_is_greater_or_equal_suite(),
                              s21_is_less_suite(),
                              s21_is_less_or_equal_suite(),
                              s21_is_not_equal_suite(),
                              s21_mul_suite(),
                              s21_sub_suite(),
                              s21_negate_suite(),
                              s21_from_decimal_to_float_suite(),
                              s21_from_decimal_to_int_suite(),
                              s21_from_int_to_decimal_suite(),
                              s21_from_float_to_decimal_suite(),
                              s21_round_suite(),
                              s21_floor_suite(),
                              s21_truncate_suite(),
                              s21_is_greater_copy_suite(),
                              NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
