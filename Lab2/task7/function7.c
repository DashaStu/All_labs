#include "task7.h"

double funk1(double x){//-5 6
    return x + 4;
}

double funk2(double x){//pi/2 -3i/2
    return sin(x) + 1;
}

double funk3(double x){//0 2
    return (x + 1)*(x - 2)*(x - 2)*(x - 2);
}

double funk4(double x){
    return x * x;
}
enum dihtomy solve(double* result, double a, double b, double epsilon, double (*funk)(double)){
    if(funk(a) * funk(b) > 0){
        return NO_ROOT;
    }
    if(epsilon <= 0){
        return INVALID_INPUT;
    }
    while(fabs(b - a) > epsilon){
        (*result) = (a + b) / 2;
        if(funk(*result) * funk(a) < 0){
            b = (*result);
        }
        else{
            a = (*result);
        }
    }
    return OK;
}