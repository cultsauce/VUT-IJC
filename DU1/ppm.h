// ppm.h
   // Řešení IJC-DU1, příklad B), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // rozhranie pre pracu s obrazkovym formatom ppm


#include <stdio.h>
#include "error.h"
#include <stdlib.h>

#ifndef PPM_H
#define PPM_H

// structure to store information about a ppm file and its contents
struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
     };

// read a ppm file specified by filename and return its contents stored in a ppm struct
struct ppm * ppm_read(const char * filename);

// free all dynamically allocated space for a ppm struct
void ppm_free(struct ppm *p);

#endif /*PPM_H*/