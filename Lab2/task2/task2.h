#ifndef LAB1_TASK2_H
#define LAB1_TASK2_H

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

enum errors{
    OK,
    INVALID_INPUT,
    OVER
};

enum errors midle_geo(double* res, int n, ...);
enum errors fast_pow(double base, int step, double* result);
#endif
