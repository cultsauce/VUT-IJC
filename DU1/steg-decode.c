// steg-decode.c
   // Řešení IJC-DU1, příklad B), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // dekodovanie dat z obrazku formatu ppm


#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.c"

#define PRIME_START 29

int main(int argc, char **argv)
{
    // no file was given, exit
    if (argc > 2 || argc == 1) 
        error_exit("steg-decode: soubor nespecifikovan\n");

    // read the file containing the secret message
    struct ppm *img = ppm_read(argv[1]);
    if (img == NULL) error_exit("steg-decode: chybny format souboru\n");
    
    // create a bitset the size of the file with prime positions marked
    bitset_alloc(primes, img->xsize * img->ysize * 3);
    Eratosthenes(primes);
    
    char byte = 0;
    unsigned bits_read = 0;
    int has_end = 0;

    for (unsigned long i = PRIME_START; i < bitset_size(primes); i++)
    {
        // if the current byte is a prime position, we need to extract data from it
        if (!bitset_getbit(primes, i))
        {
            // mask out the LSB from the current byte and save it
            byte |= ((img->data[i] & 1) << bits_read++);

            // if an entire char has been read, print it to stdout
            if (bits_read == 8)
            {
                // the current char is \0, meaning the secret message is complete
                if (byte == '\0') 
                {
                    putchar('\n');
                    has_end = 1;
                    break;
                }
                putchar(byte);
                bits_read = 0;
                byte = 0;
            }
        }
    }

    // free all dynamic memory allocated within the program
    bitset_free(primes);
    ppm_free(img);

    // missing \0 in the secret message
    if (!has_end)
    {
        error_exit("steg-decode: chybny format souboru\n");
    }
}
