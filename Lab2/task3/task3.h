#ifndef LAB1_TASK3_H
#define LAB1_TASK3_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    INVALID_FILE
};

struct Sub
{
    char * filename;
    int line;
    int index;
    int flag_open;
    struct Sub * next;
};

enum errors add_sub(struct Sub ** head, char * filename, int line, int idx, int * len);
enum errors find_substring_in_file(struct Sub ** subs, char * str, int * len_subs, int count_file, ...);
int string_len(const char * str);

#endif
