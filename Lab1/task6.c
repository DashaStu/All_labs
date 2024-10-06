#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_RECURSION_DEPTH 20

enum errors {
    INVALID_INPUT,
    OK
};

double simpsons_rule_interval(double (*func)(double), double a, double b) {
    double h = (b - a) / 2.0;
    double fa = func(a);
    double fb = func(b);
    double fm = func((a + b) / 2.0);
    return (h / 3.0) * (fa + 4.0 * fm + fb);
}

double adaptive_simpsons(double (*func)(double), double a, double b, double epsilon, double whole, int depth) {
    double mid = (a + b) / 2.0;
    double left = simpsons_rule_interval(func, a, mid);
    double right = simpsons_rule_interval(func, mid, b);
    double delta = left + right - whole;

    if (depth >= MAX_RECURSION_DEPTH) {
        return left + right;
    }

    if (fabs(delta) <= 15.0 * epsilon) {
        return left + right + delta / 15.0;
    }
    return adaptive_simpsons(func, a, mid, epsilon / 2.0, left, depth + 1) +
           adaptive_simpsons(func, mid, b, epsilon / 2.0, right, depth + 1);
}

double integrate(double (*func)(double), double a, double b, double epsilon) {
    double initial = simpsons_rule_interval(func, a, b);
    return adaptive_simpsons(func, a, b, epsilon, initial, 0);
}

double func_a(double x) {
    return log(1 + x) / x;
}

double func_b(double x) {
    return exp(-x * x / 2);
}

double func_c(double x) {
    return log(1 / (1 - x));
}

double func_d(double x) {
    return pow(x, x);
}

enum errors input_valid(char* str){
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
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("А где эпсилон?\n");
        return INVALID_INPUT;
    }
    double e;
    if (input_valid(argv[1]) != OK) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    sscanf(argv[1], "%lf", &e);
    if(e <= 0) {
        printf("Эпсилон больше нуля\n");
        return INVALID_INPUT;
    }
    double result_a = integrate(func_a, 0.000001, 1, e);
    double result_b = integrate(func_b, 0, 1, e);
    double result_c = integrate(func_c, 0, 0.9999999, e);
    double result_d = integrate(func_d, 0, 1, e);

    printf("Интеграл a: %.8lf\n", result_a);
    printf("Интеграл b: %.8lf\n", result_b);
    printf("Интеграл c: %.8lf\n", result_c);
    printf("Интеграл d: %.8lf\n", result_d);

    return 0;
}
