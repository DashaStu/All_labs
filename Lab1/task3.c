#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <float.h>

enum errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLO
};

enum root{
    TWO_ROOT,
    ONE_ROOT,
    NO_ROOT
};

int check(long double* a, long double* b, long double ep) {
    long double res = *a * *b;
    return (res - DBL_MAX <= ep && res + DBL_MAX >= ep);
}

enum errors tri(long double a, long double b, long double c, long double ep, int* res) {
    if (!(check(&a, &a, ep) && check(&b, &b, ep) && check(&c, &c, ep))) return OVERFLO;
    if (a <= ep || b <= ep || c <= ep) return INVALID_INPUT;
    if (fabsl(a * a + b * b - c * c) <= ep ||
        fabsl(a * a + c * c - b * b) <= ep ||
        fabsl(b * b + c * c - a * a) <= ep) {
        *res = 1;
    }
    else {
        *res = 0;
    }
    return OK;
}

int is_equal(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

enum root solve_quadratic(double a, double b, double c, double epsilon, double* x1, double* x2) {
    double discriminant = b * b - 4 * a * c;

    if (is_equal(discriminant, 0.0, epsilon)) {
        *x1 = -b / (2 * a);
        return ONE_ROOT;
    }
    if (discriminant > 0) {
        double sqrt_discriminant = sqrt(discriminant);
        *x1  = (-b + sqrt_discriminant) / (2 * a);
        *x2 = (-b - sqrt_discriminant) / (2 * a);
        return TWO_ROOT;
    }
    return NO_ROOT;

}

enum errors input_valid(char* str, double *res){
    int size_str = strlen(str);
    int flag_to = 0;
    if(size_str > 12) return INVALID_INPUT;
    if(str[0] == '-') return INVALID_INPUT;
    if(str[0] == '.') return INVALID_INPUT;
    for(int i = 0; i < size_str;i++){
        if (str[i] == '.') {
            if(flag_to){

                return INVALID_INPUT;
            }
            else{
                flag_to = 1;
            }
        }
        else if(!(str[i] >= '0' && str[i] <= '9')){
            return INVALID_INPUT;
        }
    }
    sscanf(str, "%lf", res);
    return OK;
}

enum errors input_valid_chislo(char* str, long int *res){
    int size_str = strlen(str);
    if(size_str > 12) return INVALID_INPUT;

    for(int i = 0; i < size_str;i++){
        if(!(str[i] >= '0' && str[i] <= '9')){
            if(str[i] == '-' && i == 0) continue;
            else
                return INVALID_INPUT;
        }
    }
    sscanf(str, "%ld", res);
    return OK;
}

void print_quadratic_solve(double a, double b, double c, double epsilon){
    double x1, x2;
    if (solve_quadratic(a,b,c,epsilon, &x1, &x2) == NO_ROOT){
        printf("Нет вещественных решений для коеффициентов a:%lf b:%lf c:%lf\n", a,b,c);
    }
    else if(solve_quadratic(a,b,c,epsilon, &x1, &x2) == ONE_ROOT){
        printf("Одно решение для коеффициентов a:%lf b:%lf c:%lf: x = %lf\n",a, b, c, x1);
    }
    else{
        printf("Два решения для коеффициентов a:%lf b:%lf c:%lf: x1 = %lf, x2 = %lf\n",a, b, c, x1, x2);
    }

}

int main(int argc, char* argv[])
{

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0')) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    switch (argv[1][1]) {
        case 'q': {
            if (argc != 6) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            double ep, a, b, c;
            if (input_valid(argv[2], &ep) != OK || ep < 0 ||
                input_valid(argv[3], &a)!= OK || input_valid(argv[4], &b) != OK ||
                input_valid(argv[5], &c) != OK || is_equal(a, 0.0, ep) ||
                is_equal(b, 0.0, ep) || is_equal(c, 0.0, ep))
            {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }

            if(is_equal(a, b, ep) && is_equal(b,c, ep)){
                print_quadratic_solve(a,b,c,ep);
                return 0;
            }
            if(is_equal(a, b, ep)){
                print_quadratic_solve(a, b, c, ep);
                print_quadratic_solve(a, c, b, ep);
                print_quadratic_solve(c, a, b, ep);
                return 0;
            }
            if(is_equal(b, c, ep)){
                print_quadratic_solve(a, b, c,ep);
                print_quadratic_solve(b,a, c,ep);
                print_quadratic_solve(b, c, a, ep);
                return 0;
            }
            if(is_equal(a, c, ep)){
                print_quadratic_solve(a, b, c,ep);
                print_quadratic_solve(b,a, c,ep);
                print_quadratic_solve(a, c, b, ep);
                return 0;
            }
            print_quadratic_solve(a, b, c,ep);
            print_quadratic_solve(b,a, c,ep);
            print_quadratic_solve(a, c, b, ep);
            print_quadratic_solve(b, c, a,ep);
            print_quadratic_solve(c, a, b, ep);
            print_quadratic_solve(c, b, a, ep);

            break;
        }
        case 'm': {
            if (argc != 4) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            long int a, b;
            if (input_valid_chislo(argv[2], &a) != OK || a == 0 ||
                input_valid_chislo(argv[3], &b) != OK || b == 0) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            if (a % b == 0) {
                printf("Первое число кратно второму\n");
            }
            else {
                printf("Первое число не кратно второму\n");
            }
            break;
        }
        case 't': {
            if (argc != 6) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            double a, b, c, ep;
            if (input_valid(argv[2], &ep) != OK || ep == 0 ||
                input_valid(argv[3], &a)!= OK || input_valid(argv[4], &b) != OK ||
                input_valid(argv[5], &c) != OK || a <= 0 || b <= 0 || c <= 0 ) {

                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            int res_t;
            enum errors status = tri(a, b, c, ep, &res_t);
            if (status == OVERFLO) {
                printf("Переполнение\n");
                return OVERFLO;
            }
            else if (status == INVALID_INPUT) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            if (res_t) printf("Стороны могут образовать прямоугольный треугольник\n");
            else printf("Стороны НЕ могут образовать прямоугольный треугольник\n");
            break;
        }
        default: {
            printf("Нет такого флага\n");
            return INVALID_INPUT;
        }
    }
}
