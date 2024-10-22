#ifndef LAB1_TASK8_H
#define LAB1_TASK8_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};
enum errors sum_num(char** result, const int base, char* num1, char* num2);
enum errors sum_numbers(char** result, int base, int count, ...);
void first_0(char** result);

#endif //LAB1_TASK8_H
