// htab_resize.c
   // Řešení IJC-DU2, příklad B), 11.4.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // zmeni velkost pola hashovacej tabulky

#include "htab.h"
#include "struct_htab.h"


void htab_resize(htab_t *t, size_t newn)
{
    if (newn <= 0)
        return;
        
    // the new size is bigger than the old, allocate more space
    if (newn >= t->arr_size)
    {
        htab_item_t **tmp = realloc(t->arr_ptr, newn * sizeof(htab_item_t *));
        if (tmp == NULL) return;
        t->arr_ptr = tmp;

        // initialize all newly added buckets
        for (size_t i = t->arr_size; i < newn; i++)
        {
            t->arr_ptr[i] = NULL;
        }
    }

    size_t old_size = t->arr_size;
    
    for (size_t i = 0; i < old_size; i++)
    {
        // iterate over all items in the old table and move all, whose hash value changed
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL)
        {
            // if the newly generated hash is different from the old one, move the element
            if ((htab_hash_function(head->item.key) % newn) != i)
            {    
                t->arr_size = newn;
                htab_pair_t *tmp = htab_lookup_add(t, head->item.key);
                t->size--;
                tmp->value = head->item.value;

                head = head->next;

                t->arr_size = old_size;
                htab_erase(t, tmp->key);
                continue;
            }
            head = head->next;
        }
    }

    // if the new size is smaller, free all (now redundant) space
    if (newn < t->arr_size)
    {
        htab_item_t **tmp = realloc(t->arr_ptr, newn * sizeof(htab_item_t *));
        if (tmp == NULL) return;
        t->arr_ptr = tmp;
    }
    t->arr_size = newn;
}
