#include "s21_decimal.h"

#define MAX_PRECISION 7
void round_dec(double *num) {
  double tmp = *num;
  if (*num > 999999) {
    int i = 0;
    for (; tmp > 9999999; i += 1) {
      tmp /= 10;
    }
    tmp = round(tmp);

    for (int j = 0; j < i; j++) {
      tmp *= 10;
    }
    *num = (long long int)tmp;
  }
}

void put_slice(char *str_num, int *postdot) {
  int slice = 0;
  int flag = 1;
  for (int i = strlen(str_num) - 1; i > 0; i--) {
    if (str_num[i] == '0' && flag == 1) {
      slice = i;
      *postdot -= 1;
    } else {
      flag = 0;
    }
  }
  if (slice > 0) {
    str_num[slice] = '\0';
  }
}

void from_float_to_str(int *predot, int *postdot, int *dot_index, char *str,
                       char *str_num, double src, int *sign) {
  sprintf(str, "%.10lf", src);
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '.') {
      *dot_index = i;
      *predot = i;
      for (int j = i; j < (int)strlen(str) - 1; j++) {
        str[j] = str[j + 1];
      }
      str[strlen(str) - 1] = '\0';
    }
  }
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '-') {
      *predot -= 1;
      *sign = 1;
      *postdot -= 1;
    } else if (str[i] != '0') {
      if (fabs(src) < 1) {
        int j = i;
        for (; j < 7 + i; j += 1) {
          str_num[j - i] = str[j];
        }
        *postdot += j;
      } else {
        int j = i;
        for (; (j < *dot_index) || j < i + 7; j += 1) {
          str_num[j - i] = str[j];
        }
        *postdot += j;
      }
      i = strlen(str);
    }
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (isnan(src) != 0 || isinf(src) != 0 || !dst) {
    return ERROR;
  }
  if (src > DECIMAL_MAX) {
    return ERROR;
  }
  int predot = 0, postdot = 0, shift = 0, sign = 0, ret_num = 0, dot_index = 0;
  double copy_src = src;
  char str[1000] = "\0";
  char str_num[1000] = "\0";
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  if (src - (int)src == 0) {
    round_dec(&copy_src);
    ret_num = s21_from_int_to_decimal(copy_src, dst);
  } else {
    int i = 0;
    if (fabs(copy_src) < 999999) {
      for (; fabs(copy_src) < 999999; i += 1) {
        copy_src *= 10;
      }
      copy_src = round(copy_src);
      for (int j = 0; j < i; j++) {
        copy_src /= 10;
      }
    }
    from_float_to_str(&predot, &postdot, &dot_index, str, str_num, copy_src,
                      &sign);
    put_slice(str_num, &postdot);
    sscanf(str_num, "%lf", &copy_src);
    round_dec(&copy_src);
    shift = postdot - predot;
    dst->bits[0] = (long long int)copy_src;
    dst->bits[3] = shift << 16 | sign << 31;
  }
  return ret_num;
}
