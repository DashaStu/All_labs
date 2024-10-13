#ifndef LAB1_TASK7_H
#define LAB1_TASK7_H

#include <stdio.h>
#include <math.h>
enum dihtomy{
    OK,
    INVALID_INPUT,
    NO_ROOT
};
enum dihtomy solve(double* result, double a, double b, double epsilon, double (*funk)(double));
double funk1(double x);
double funk2(double x);
double funk3(double x);
double funk4(double x);
#endif
