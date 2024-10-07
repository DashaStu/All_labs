#ifndef LAB1_TASK1_H
#define LAB1_TASK1_H

#include <stdio.h>
#include <stdlib.h>

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

int len_str(const char* str);
enum errors reverse_str(const char* str, char** result);
enum errors up_str(const char* str, char** result);
enum errors str_swap_symbol(const char * str, char** result);
enum errors str_to_u_int(const char* str, unsigned int* result);
void contation(char* str, char ** result, int* len);
enum errors str_con(int count_str, char** str, char** result, unsigned int seed);

#endif
