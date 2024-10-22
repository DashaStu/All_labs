#include "task7.h"

int main(){
    double res_funk;
    double a = -5;
    double b = 3 * M_PI/2;
    enum dihtomy res = solve(&res_funk, a, b, 0.00001, funk1);
    if(res == OK){
        printf("Have solve: %lf\n", res_funk);
    }
    else if(res == NO_ROOT){
        printf("Not have solve\n");
    }
    else{
        printf("Invalid input\n");
    }

    return 0;
}