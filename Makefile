
all: test.o bloom.o
	gcc -o test test.o bloom.o

