#include "task2.h"

enum errors midle_geo(double* res, int n, ...){
    if(n <= 0){
        return INVALID_INPUT;
    }
    va_list temp;
    *res = 1;
    va_start(temp, n);
    for(int i =0 ;i <n;i++){
        *res *= va_arg(temp, double);
        if(isnan(*res) || isinf(*res)) {
            va_end(temp);
            return OVER;
        }
    }
    va_end(temp);
    *res = pow(*res, 1.0 / n);
    return OK;
}
enum errors fast_pow(double base, int step, double* result){
    enum errors temp;
    if(step < 0){
        temp = fast_pow(1.0/base, -1 * step, result);
        return temp;
    }
    if(step == 0){
        *result = 1;
        return OK;
    }
    if(step % 2 == 0)
    {
        temp = fast_pow(base, step / 2, result);
        if(isnan(*result) || isinf(*result))
        {
            return OVER;
        }
        *result *= *result;
    }
    else
    {
        temp = fast_pow(base, step - 1, result);
        if(isnan(*result) || isinf(*result))
        {
            return OVER;
        }
        *result *= base;
    }
    return temp;

}