#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IT 30

enum errors {
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVER
};

double sum_a(double x, double epsilon) {
    double term = 1;
    double sum = 1;
    int n = 1;
    while(fabsl(term) >= epsilon && n < MAX_IT){
        term *= x /n;
        sum += term;
        n++;
    }

    return sum;
}
double sum_b(double x, double epsilon) {
    double term = 1;
    double sum = 1;
    int n = 1;

    while (fabsl(term) > epsilon && n < MAX_IT) {
        if(2 * n * (2 * n -1) == 0) return sum;
        term *= (- x * x)/(2 * n * (2 * n -1));
        sum +=term;
        n++;
    }

    return sum;
}

double sum_c(double x, double epsilon) {
    double term = 1;
    double sum = term;
    int n = 1;

    while (fabsl(term) > epsilon && n < MAX_IT) {
        if(9 * n * n - 9*n + 2 == 0) return sum;
        term *= (9*x*x*n*n)/(9*n*n - 9*n +2);
        sum += term;
        n++;
    }

    return sum;
}


double sum_d(double x, double epsilon) {
    double term = 1;
    double sum = 0;
    int n = 1;
    do{
        if(2*n == 0) return sum;
        term *=(- x * x *(2*n-1))/(2*n);
        sum += term;
        n++;
    }while(fabsl(term) > epsilon && n < MAX_IT);


    return sum;
}

enum errors input_valid(char* str, double *res){
    int size_str = strlen(str);
    int flag_to = 0;
    if(size_str > 5) return INVALID_INPUT;
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

enum errors input_valid_chislo(char* str, double *res){
    int size_str = strlen(str);
    int flag_to = 0;
    if(size_str > 12) return INVALID_INPUT;
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

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    double e;
    double x;
    if (input_valid(argv[1], &e) != OK || e == 0) {
        printf("Некорректный эпсилон\n");
        return INVALID_INPUT;
    }

    if (input_valid_chislo(argv[2], &x) != OK || x == 0) {
        printf("Некорректный ввод числа\n");
        return INVALID_INPUT;
    }
    double  res_a = sum_a(x, e);
    double  res_b = sum_b(x, e);
    double  res_c = sum_c(x, e);
    double  res_d = sum_d(x, e);

    printf("Результат суммы а: %lf\n", res_a);
    printf("Результат суммы b: %lf\n", res_b);
    if (fabs(x) < 1) {
        printf("Результат суммы c: %lf\n", res_c);
        if(res_d != -1)
            printf("Результат суммы d: %lf\n", res_d);
        else{
            printf("Переполнение факториала\n");
        }
    }
    else {
        printf("Для суммы с, d есть ограничения\n");
    }
    printf("%lu", sizeof(long double));
    return 0;
}