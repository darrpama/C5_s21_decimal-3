OS := $(shell uname -s)
CC = gcc
CFLAGS = -O1 -Wall -Wextra -Werror -std=c11

BINARY = arithmetic/s21_binary_arithmetic
ADD = arithmetic/s21_add
DIV = arithmetic/s21_div
MUL = arithmetic/s21_mul
SUB = arithmetic/s21_sub
MOD = arithmetic/s21_mod
SHIFTS = binary_shifts/s21_binary_shifts
SCALE = scale/s21_scale
CONVERTERS = converters/s21_converters
BIT = support/bit_operations
SUPPORT = support/support_materials
COMPARISON = comparison/s21_comparison
OTHER = other_func/s21_other_func
O_FILES = s21_binary_arithmetic.o s21_add.o s21_div.o s21_mul.o s21_sub.o s21_mod.o s21_binary_shifts.o s21_converters.o s21_comparison.o s21_scale.o bit_operations.o s21_other_func.o
C_FILES = $(BINARY).c $(ADD).c $(DIV).c $(MUL).c $(SUB).c $(MOD).c $(SHIFTS).c $(CONVERTERS).c $(BIT).c $(COMPARISON).c $(SCALE).c $(OTHER).c
H_FILES = s21_decimal.h

ifeq ($(OS), Darwin)
	CHKFLAGS = -lcheck
else
	CHKFLAGS = -lcheck -lrt -lm -lpthread -lsubunit
endif

all: clean s21_decimal.a test1
	make clean
	rm s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar rc s21_decimal.a $(O_FILES)
	ranlib s21_decimal.a

s21_decimal.o:
	$(CC) $(CFLAGS) -c $(C_FILES)

test1: decimal_test.o s21_decimal.o
	$(CC) $(CFLAGS) $(O_FILES) decimal_test.o -o test.out $(CHKFLAGS)
	./test.out

another_test: another_test.o s21_decimal.o
	$(CC) $(CFLAGS) $(O_FILES) another_test.o -o test.out $(CHKFLAGS)
	./test.out

test:
	@make test1

gcov_report: decimal_test.o s21_decimal.o
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > decimal_test.c
	$(CC) $(CFLAGS) --coverage -l check $(C_FILES) decimal_test.c -o test $(CHKFLAGS)
	./test
	lcov -t "./test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm decimal_test.c

another_test.o:
	checkmk clean_mode=1 tests1.check > another_test.c
	$(CC) $(CFLAGS) -c another_test.c -o another_test.o $(CHKFLAGS)
	rm another_test.c

decimal_test.o:
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > decimal_test.c
	$(CC) $(CFLAGS) -c decimal_test.c -o decimal_test.o $(CHKFLAGS)
	rm decimal_test.c

check:
	cp ../materials/linters/.clang-format .
	cppcheck $(C_FILES) *.h
	clang-format -n $(C_FILES) *.h
    

clean: 
	@rm -rf *.o *.gcda *.gcno *.out *.gch *.info
	@rm -rf test
	@rm -rf report
