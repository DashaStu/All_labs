#include "task2.h"

int main(){
    double res;
    enum errors res_midle_geo = midle_geo(&res, 5, 2.0, 2.5, 4.3, 3.0, 1.5);
    if(res_midle_geo == INVALID_INPUT){
        printf("Invalid input\n");
        return INVALID_INPUT;
    }
    if(res_midle_geo == OVER){
        printf("We take OVERFLOW\n");
        return OVER;
    }
    printf("%lf\n", res);

    double res_pow;
    double base = 4;
    int step = 2;
    enum errors res_fast_pow = fast_pow(base, step, &res_pow);
    if(res_fast_pow == OVER){
        printf("We take Overflow\n");
        return OVER;
    }
    printf("%lf\n", res_pow);

    return 0;
}