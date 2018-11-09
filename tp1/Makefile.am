AM_CFLAGS = -pedantic -Wall -Wextra -std=gnu17
AM_LDFLAGS = -lpthread

bin_PROGRAMS = exercise1 exercise2 exercise3
exercise1_SOURCES = exercise1.c common.c
exercise2_SOURCES = exercise2.c common.c bheap.c
exercise3_SOURCES = exercise3.c common.c

test-exercise1: exercise1
	./exercise1 tests/test1-input.txt | diff tests/test1-output.txt -
	./exercise1 tests/test2-input.txt | diff tests/test2-output.txt -

test-exercise2: exercise2
	./exercise2 tests/test1-input.txt | diff tests/test1-output.txt -
	./exercise2 tests/test2-input.txt | diff tests/test2-output.txt -
