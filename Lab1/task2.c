#include <stdio.h>
#include <string.h>
#include <math.h>

enum errors {
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLO
};

double limit_e(double epsilon)
{
    double n = 1;
    double current = 0, previous = 0;
    do
    {
        previous = current;
        n *= 2;
        current = pow((1.0 + 1.0 / n) , n);
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_pi(double epsilon)
{
    int n = 2;
    double current = 4.0, previous = 0;
    do
    {
        previous = current;
        current *= (4.0 * n * ( n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_ln(double epsilon)
{
    double n = 1;
    double current = 0, previous = 0;
    do
    {
        previous = current;
        n *= 2;
        current = n * (pow(2.0, 1.0 / n) - 1.0);
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_sqrt(double epsilon)
{
    double n = 1;
    double current = -0.5, previous = 0;
    do
    {
        previous = current;
        n ++;
        current = (2.0 * previous - pow(previous, 2.0) + 2.0)/2.0;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double sum_H(int n)
{
    double sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum += 1.0/i;
    }

    return sum;

}

double limit_y(double epsilon)
{
    double previous = 0;
    double current = 1;
    int n = 1;
    do
    {
        previous = current;
        n *= 2;
        current = sum_H(n) - log(n);

    } while (fabs(previous - current) >= epsilon);

    return current;
}

double row_e(double epsilon)
{
    double current = 1.0, previous = 0, term= 1.0;
    int n = 1;
    while(fabsl(previous - current) >= epsilon){
        previous = current;
        term *= 1.0 / n;
        current += term;
        n++;
    }
    return previous;
}

double row_pi(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;
    do
    {
        previous = current;
        n++;
        current -= 1.0/(2.0 * n - 1.0);
        n++;
        current += 1.0/(2.0 * n - 1.0);
    } while (fabs(previous - current) >= epsilon);
    return current * 4;
}

double row_ln(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;
    do
    {
        previous = current;
        n++;
        current -= 1.0/n;
        n++;
        current += 1.0/n;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double row_sqrt(double epsilon)
{
    int k = 2;
    double current = pow(2.0, 1.0/4.0), previous = 0;
    do
    {
        previous = current;
        ++k;
        current *= pow(2,1.0/pow(2,k));
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double row_y(double epsilon)
{
    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;
    do
    {
        previous = current;
        k++;
        l = sqrt(k);
        if (fabs(fmod(l,1.0)) < epsilon)
        {
            k++;
            l = (int)pow(k, 0.5);
        }
        current += 1.0/pow((int)l,2.0) - 1.0/k;


    } while (fabs(previous - current) >= epsilon);

    return (current - pow(M_PI,2) / 6);
}

double equation_e(double epsilon)
{
    double x = 3;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = log(x) - 1;
        df = 1.0 / x;
        x = x - f / df;
    }
    return x;
}

double equation_pi(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = cos(x) + 1;
        df = -sin(x);
        x = x - f / df;
    }
    return x;
}

double equation_ln(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }
    return x;
}

double equation_sqrt(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = x * x - 2;
        df = 2 * x;
        x = x - f / df;
    }
    return x;
}

int is_prime (int number)
{
    if(number < 0) number *= -1;

    if (number == 0 || number == 1 || number == 2)
        return 0;

    if(number % 2 == 0) return 1;

    for (int i = 3; i <= floor(sqrt(number)); i+=2)
    {
        if (number % i == 0)
            return 1;
    }
    return 0;
}

double equation_y(double epsilon)
{
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;
    double product = 0.5;
    do
    {
        previous = current;
        do
        {
            p++;
        } while (is_prime(p));
        product *= (p - 1.0)/p;
        current = log(p) * product;


    } while (fabs(previous - current) >= epsilon);
    return (-log(current));
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
    /*int i = -10, j;
    char *p = (char *)&i;
    for (j = 0; j < sizeof(int); ++j)
    {
        printf("%d ", *p++);
    }

    return 0;*/
    if(argc != 2){
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    double e;
    if(input_valid(argv[1]) != OK){
        printf("Некорректный епсилон\n");
        return INVALID_INPUT;
    }
    sscanf(argv[1], "%lf", &e);
    if(e <= 0){
        printf("e must be > 0\n");
        return INVALID_INPUT;
    }
    printf("\tПредел\tРяд\tУравнение\n");
    printf("e:    %lf %lf %lf\n", limit_e(e), row_e(e), equation_e(e));
    printf("Pi:   %lf %lf %lf\n", limit_pi(e), row_pi(e), equation_pi(e));
    printf("ln2:  %lf %lf %lf\n", limit_ln(e), row_ln(e), equation_ln(e));
    printf("sqrt(2):%lf %lf %lf\n", limit_sqrt(e), row_sqrt(e), equation_sqrt(e));
    printf("Gamma:  %lf %lf %lf\n", limit_y(e), row_y(e), equation_y(e));

    return 0;
}
