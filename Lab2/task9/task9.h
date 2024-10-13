#ifndef LAB1_TASK9_H
#define LAB1_TASK9_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
};

enum errors drob(double** result,int* len, int count, int base, ...);
int gcd(int a, int b);

#endif //LAB1_TASK9_H
