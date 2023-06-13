CCF = gcc -Wall -Wextra -Werror -std=c11

all: s21_string.a test gcov_report

test: s21_string.a
	$(CCF) s21_tests.c s21_string.a -L./ -coverage -o test.out -lcheck
	rm -rf s21_test.gcno

s21_string.a:
	$(CCF) -c s21_string.c s21_string_io.c s21_string_special.c
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm -rf *.o

gcov_report: test
	./test.out
	gcov *.gcda
	geninfo ./ -b ./ -o report.info
	genhtml -o report report.info;
	rm -rf *.info *.gcda *.gcno

check: test
	cp ../materials/linters/cpplint.py ./cpplint.py
	cp ../materials/linters/CPPLINT.CFG ./CPPLINT.CFG
	python3 cpplint.py *.c
	python3 cpplint.py *.h
	leaks -atExit -- ./test.out 
clean:
	rm -rf *.info *.gcda *.gcno report *.out *.o *.a *.gcov
	rm -rf report a.out.dsym CPPLINT.CFG cpplint.py *.dSYM
