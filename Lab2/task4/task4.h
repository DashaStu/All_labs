#ifndef LAB1_TASK4_H
#define LAB1_TASK4_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_N_SIZE 100
enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVER
};

typedef struct{
    double x;
    double y;
}Point;

enum errors polynomial_n(double* res, double x, int n, ...);
double turn(Point first, Point second, Point third);
bool convex_polygon(int n, ...);
bool is_valid_number(const char* num_str, const int base);
bool is_valid_digit(const char c, const int base);
bool is_kaprekar(long num, const int base);
enum errors kaprekar(char** result, int base, int count, ...);

#endif
