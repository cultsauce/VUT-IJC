// bitset.h
// Řešení IJC-DU1, příklad A), 20.3.2022
// Autor: Tereza Kubincova, FIT
// Přeloženo: gcc 9.3.0
// rozhranie pre pracu s bitovym polom

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include "error.h"

#ifndef BITSET_H
#define BITSET_H

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define BYTES(velikost)                                                                                 \
        (((velikost) % (sizeof(bitset_index_t) * CHAR_BIT) == 0) ? ((velikost) / (sizeof(bitset_index_t) * CHAR_BIT) + 1) \
                                                        : ((velikost) / (sizeof(bitset_index_t) * CHAR_BIT) + 2))

#define bitset_create(jmeno_pole, velikost)                                                       \
        static_assert((velikost) > 0 && (velikost) <= ULONG_MAX, "bitset_create: zla velikost pole"); \
        bitset_index_t jmeno_pole[BYTES((velikost))] = {(velikost), 0};                                        

#define bitset_alloc(jmeno_pole, velikost)                                     \
        assert((velikost) > 0 && (velikost) <= ULONG_MAX);                         \
        bitset_t jmeno_pole = calloc(BYTES((velikost)), sizeof(bitset_index_t)); \
        if (jmeno_pole == NULL)                                                \
                error_exit("%s\n", "bitset_alloc: Chyba alokace paměti\n");    \
        jmeno_pole[0] = (velikost);

#ifndef USE_INLINE

#define bitset_free(jmeno_pole) \
        free(jmeno_pole)

#define bitset_size(jmeno_pole) \
        (jmeno_pole[0])

#define bitset_setbit(jmeno_pole, index, vyraz) \
        (index >= jmeno_pole[0]) ? \
        (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (index), jmeno_pole[0] - 1), 0) \
        : (((vyraz) == 0) ? \
        (jmeno_pole[((index) / (sizeof(bitset_index_t) * CHAR_BIT)) + 1] &= ~(1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT)))) \
        : (jmeno_pole[((index) / (sizeof(bitset_index_t) * CHAR_BIT)) + 1] |= (1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT)))))

#define bitset_getbit(jmeno_pole, index) \
        (((index) >= jmeno_pole[0]) ? \
        (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (index), jmeno_pole[0] - 1), 0) \
        : (jmeno_pole[((index) / (sizeof(bitset_index_t) * CHAR_BIT)) + 1] & (1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT)))))

#else

extern inline void bitset_free(bitset_t jmeno_pole)
{
        free(jmeno_pole);
}

extern inline bitset_index_t bitset_size(bitset_t jmeno_pole)
{
        return jmeno_pole[0];
}

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz)
{
        if (index >= bitset_size(jmeno_pole))
        {
                error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", index, jmeno_pole[0] - 1);
        }
        bitset_index_t idx = (index / (sizeof(bitset_index_t) * CHAR_BIT)) + 1;
        bitset_index_t help = 1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT));
        jmeno_pole[idx] = (vyraz == 0) ? (jmeno_pole[idx] & ~help) : (jmeno_pole[idx] | help);
}

extern inline unsigned char bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
        if (index >= bitset_size(jmeno_pole))
        {
                error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, jmeno_pole[0] - 1);
        }
        bitset_index_t idx = ((index) / (sizeof(bitset_index_t) * CHAR_BIT)) + 1;
        bitset_index_t help = 1UL << ((index) % (sizeof(bitset_index_t) * CHAR_BIT));
        return (jmeno_pole[idx] & help) == 0 ? 0 : 1;
}

#endif
#endif /*BITSET_H*/