// primes.c
   // Řešení IJC-DU1, příklad a), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // vypise poslednych 10 prvocisiel od 2 do 300000000

#include <time.h>
#include "eratosthenes.c"

#define N 100500UL
#define NUM_PRINT 10

int main()
{
    // initialize the clock for measuring the running time
    clock_t start = clock();

    // create a bitset of size 300000000 and mark all prime numbers in it
    bitset_create(pole, N);
    Eratosthenes(pole);

    unsigned long last_ten[NUM_PRINT], idx = 0;

    // find the last 10 prime numbers in the bitset by iterating over the bitset in descending order
    for (unsigned long i = bitset_size(pole) - 1; i != 0; i--)
    {
        if (!bitset_getbit(pole, (bitset_index_t) i))
        {
            last_ten[idx++] = i;
            if (idx == NUM_PRINT) break;
        }
    }

    // print the last 10 prime numbers in ascending order
    for (int j = NUM_PRINT - 1; j >= 0; j--)
    {
        printf("%lu\n", last_ten[j]);
    }

    // print the time it took to execute the programm
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
