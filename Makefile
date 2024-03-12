FLAGS  = -g -D_POSIX_C_SOURCE=200809L -Wall -Wextra -std=c11
UNAME_S := $(shell uname -s)
SCAN_FLAGS = -fprofile-arcs  -ftest-coverage

ifeq ($(UNAME_S),Linux)
	GCOV_FLAGS= -lcheck -lm -lrt -lpthread -lsubunit
	OPEN_CMD = xdg-open

endif

ifeq ($(UNAME_S),Darwin)
	GCOV_FLAGS= -fprofile-arcs  -ftest-coverage -lcheck
	OPEN_CMD = open
endif

all: clean gcov_report

s21_decimal.a:
	gcc -std=c11 $(FLAGS) -c s21_*.c
	ar rcs s21_decimal.a *.o
	rm -rf *.o

test : clean s21_decimal.a
	gcc $(FLAGS) tests/*.c *.c  $(GCOV_FLAGS) $(SCAN_FLAGS) s21_decimal.a  -o s21_test
	mkdir report_files
	mv *.gcno report_files/.
	./s21_test
	mv *.gcda report_files/.

gcov_report: clean s21_decimal.a test
	lcov --quiet --capture --directory ./report_files --output-file report_files/coverage.info
	lcov --remove report_files/coverage.info '/usr/local/lib/gcc/10/gcc/x86_64-apple-darwin20/10.3.0/include-fixed' -o report_files/filtered_coverage.info
	lcov --remove report_files/filtered_coverage.info 'tests' -o report_files/filtered_coverage.info
	genhtml --quiet report_files/filtered_coverage.info --output-directory report
	$(OPEN_CMD) report/index.html

clang:
	clang-format -style=Google -n s21_*.c
	clang-format -style=Google -n s21_*.h
	clang-format -style=Google -n  tests/*.c
	clang-format -style=Google -n  tests/*.h

clean :
	rm -rf s21_test
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda *.o
	rm -rf *.html
	rm -rf *.info
	rm -rf *.css
	rm -rf report
	rm -rf report_files
	rm -rf s21_test.dSYM

.PHONY: clean
