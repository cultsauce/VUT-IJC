// wordcount.c
   // Řešení IJC-DU2, příklad B), 11.4.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // nacita slova zo standardneho vstupu a vypise ich + pocet vyskytov

#include "htab.h"
#include "io.c"

#define MAX_WORD_LEN 127
#define INIT_SIZE 250493 // produces reasonable time on larger files

// function for printing the key, value pairs
void print_htab_pair(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

int main()
{
    htab_t * tab = htab_init(INIT_SIZE);
    if (tab == NULL)
    {
    	fprintf(stderr, "failed to allocate hash table\n");
    	return 1;
    }
    char word[MAX_WORD_LEN + 1];
    int res, err_msg = 0;
    do 
    {
        res = read_word(word, MAX_WORD_LEN + 1, stdin);
        if (strlen(word) != 0)
        {
            // if the max length is exceeded, the error message should be printed only once
            if (res >= MAX_WORD_LEN + 1 && !err_msg) 
            {
                err_msg = 1;
                fprintf(stderr, "maximum word length reached\n");
            }
            htab_pair_t *item = htab_lookup_add(tab, word);
            if (item == NULL) fprintf(stderr, "could not add word to table\n");
        }
    }
    while(res != EOF);

    // print items and counts
    htab_for_each(tab, print_htab_pair);

    // clean up
    htab_free(tab);
}
