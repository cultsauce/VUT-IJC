// tail.c
   // Řešení IJC-DU2, příklad B), 11.4.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // vypise poslednych n riadkov suboru
   // v pripade nezadanej hodnoty n sa pouzije hodnota 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 4095

void tail_file(FILE *f, int num_lines)
{
    char lines[num_lines][MAX_LINE_LEN + 2]; // \0 and newline
    int idx = 0, circular = 0, c, err_msg = 0;
    while (fgets(lines[idx], MAX_LINE_LEN + 2, f) != NULL)
    {
        if (lines[idx][strlen(lines[idx]) - 1] != '\n')
        {
            if (!err_msg) fprintf(stderr, "line exceeds the maximum allowed length\n");
            err_msg = 1;

            // discard the rest of the long line
            while ((c = fgetc(f)) != EOF) 
            {
                if (c == '\n') break;
            }

        }
        
        lines[idx][strlen(lines[idx]) - 1] = '\0';
        
        idx++;
        if (idx >= num_lines)
        {
            circular = 1;
            idx = 0; // start rewriting strings from the start
        }
    }

    // print out in the right order
    if (circular)
    {
        for (int i = idx; i < num_lines; i++)
        {
            printf("%s\n", lines[i]);
        }
    }
    
    for (int i = 0; i < idx; i++)
    {
        printf("%s\n", lines[i]);
    }
}

int parse_number_of_lines(char *flag, char *arg)
{
    int num = 0;
    char *endptr = NULL;
    if (strcmp(flag, "-n") == 0)
    {
        num = strtoul(arg, &endptr, 10);
        if (strlen(endptr) != 0)
        {
            fprintf(stderr, "invalid argument passed to -n\n");
            return -1;
        }
        return num;
    }
    else 
    {
        fprintf(stderr, "invalid arguments supplied\n");
        return -1;
    }
}

int main(int argc, char **argv)
{
    int num_lines = 10;
    FILE *f = NULL;

    switch (argc)
    {
        case 1: {
            f = stdin;
            break;
        }
        case 2: {
            f = fopen(argv[1], "r");
            break;
        }
        case 3: {
            f = stdin;
            num_lines = parse_number_of_lines(argv[1], argv[2]);
            break;
        }
        case 4: {
            if (strcmp(argv[1], "-n") == 0)
            {
                num_lines = parse_number_of_lines(argv[1], argv[2]);
                f = fopen(argv[3], "r");
            }
            else
            {
                num_lines = parse_number_of_lines(argv[2], argv[3]);
                f = fopen(argv[1], "r");
            }
            
            break;
        }
        default: {
            fprintf(stderr, "invalid number of arguments\n");
            return 1;
        }
    }
    if (num_lines == -1)
    {
        return 1;
    }
    if (f == NULL)
    {
        fprintf(stderr, "error opening file\n");
        return 1;
    }
    tail_file(f, num_lines);
    if (fclose(f) != 0)
    {
        fprintf(stderr, "could not close file\n");
        return 1;
    }
    return 0;
}
