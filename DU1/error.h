// error.h
   // Řešení IJC-DU1, příklad B), 20.3.2022
   // Autor: Tereza Kubincova, FIT
   // Přeloženo: gcc 9.3.0
   // rozhranie pre vypis chybovych hlaseni


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef ERROR_H
#define ERROR_H

// prints a warning message to stderr with the format specified by fmt
void warning_msg(const char *fmt, ...);

// prints a warning message to stderr with the format specified by fmt
// terminates the calling proccess with an exit code 1
void error_exit(const char *fmt, ...);

#endif /*ERROR_H*/
