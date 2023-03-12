CC=gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
DEPEND = error.h ppm.h
.PHONY: clear run

all: primes primes-i steg-decode

primes: error.o bitset.h primes.c eratosthenes.c
	$(CC) $(CFLAGS) error.o primes.c -o primes -lm

primes-i: error.o bitset.h primes.c eratosthenes.c
	$(CC) -DUSE_INLINE $(CFLAGS) primes.c error.o -o primes-i -lm

steg-decode: error.o bitset.h ppm.o steg-decode.o
	$(CC) $(CFLAGS) error.o ppm.o steg-decode.o -o steg-decode -lm

%.o: %.c $(DEPEND)
	$(CC) -c -o $@ $< $(CFLAGS)

run: all
	ulimit -s 40000 && ./primes
	ulimit -s 40000 && ./primes-i

clear:
	rm *.o
	rm primes primes-i steg-decode
