all:
	gcc -Wall --pedantic -lm src/*.c tests/test_gen.c -o bin/gauss

test: all
	bin/gauss 1 tests/results/test_ tests/data/test_
