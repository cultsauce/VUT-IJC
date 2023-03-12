// eratosthenes.c
   // Řešení IJC-DU1, příklad A), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // vypocita prvocisla od 2 do N (velkost bitoveho pola)

#include <math.h>
#include "bitset.h"
#include "error.h"

#ifndef ERATOSTHENES
#define ERATOSTHENES

void Eratosthenes(bitset_t pole)
{
    // 0 and 1 are not prime numbers, leave them out
    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    // 0 = prime, 1 = not prime
    for (bitset_index_t i = 2, limit = sqrt(bitset_size(pole)); i <= limit; i++)
    {
        // check if the current number is marked as prime
        if (!bitset_getbit(pole, i))
        {
            // if a prime number has been found, mark all of its multiples as being not prime
            for (bitset_index_t j = 2 * i; j < bitset_size(pole); j += i)
            {
                bitset_setbit(pole, j, 1);
            }
        } 
    }
}
#endif /*ERATOSTHENES*/