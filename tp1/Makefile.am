AM_CFLAGS = -pedantic -Wall -Wextra -std=gnu17
AM_LDFLAGS = -lpthread

bin_PROGRAMS = exercise1 exercise2 exercise-addendum
exercise1_SOURCES = exercise1.c common.c
exercise2_SOURCES = exercise2.c common.c bheap.c
exercise_addendum_SOURCES = exercise-addendum.c common.c bheap.c

test-suite: test-exercise1 test-exercise2 test-exercise-addendum

test-exercise1: exercise1
	./exercise1 tests/test1-input.txt | diff tests/test1-output.txt -
	./exercise1 tests/test2-input.txt | diff tests/test2-output.txt -

test-exercise2: exercise2
	./exercise2 tests/test1-input.txt | diff tests/test1-output.txt -
	./exercise2 tests/test2-input.txt | diff tests/test2-output.txt -

test-exercise-addendum: exercise-addendum
	./exercise-addendum tests/test1-input.txt | diff tests/test1-output.txt -
	./exercise-addendum tests/test2-input.txt | diff tests/test2-output.txt -
