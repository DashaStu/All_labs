#ifndef LAB1_TASK1_H
#define LAB1_TASK1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum errors reverse_str(char** result, const int len);
enum errors to_2r (int number, int r, char** result);

#endif //LAB1_TASK1_H
