// ppm.c
   // Řešení IJC-DU1, příklad B), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // definicie funkcii pre pracu s obrazkovym formatom ppm

#include "ppm.h"

void ppm_free(struct ppm *p)
{
    free(p);
}

struct ppm * ppm_read(const char * filename)
{
    FILE *f = NULL;
    struct ppm *p = NULL;

    f = fopen(filename, "rb");
    if (f == NULL) 
    {
        error_exit("ppm_read: soubor %s nelze otevrit\n", filename);
    }

    char format[3]; int maxval; unsigned xsize, ysize;
    size_t count = fscanf(f, "%2s %u %u %d %*[  \n]s", format, &xsize, &ysize, &maxval);
    
    if (count != 4 || maxval != 255 || format[0] != 'P' || format[1] != '6')
    {
        fclose(f);
        warning_msg("ppm_read: chybny format souboru\n");
        return NULL;
    }

    p = malloc(sizeof(struct ppm) + (xsize * ysize * 3 * sizeof(char)));
    if (p == NULL) 
    {
        fclose(f);
        error_exit("ppm_read: zlyhala alokace pameti\n");
    }
    p->xsize = xsize;
    p->ysize = ysize;

    count = fread(p->data, sizeof(char), p->xsize*p->ysize*3, f);
    if (count != p->xsize*p->ysize*3 || fgetc(f) != EOF) 
    {
        ppm_free(p);
        fclose(f);
        warning_msg("ppm_read: chybny format souboru\n");
        return NULL;
    }

    if (fclose(f) != 0)
    {
        error_exit("ppm_read: soubor se neobjevilo uspesne uzavrit\n");
    }
    return p;
}