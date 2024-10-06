#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <errno.h>

enum errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum errors numbers(long int a, int** b, int* kol) {
    if (a == 0) {
        return INVALID_INPUT;
    }
    int cap = 4;
    *b = (int*)malloc(cap * sizeof(int));
    if (!*b) return INVALID_MEMORY;
    *kol = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % a == 0) {
            (*b)[(*kol)++] = i;
        }
        if (cap == *kol) {
            cap *= 2;
            int* b_r = (int*)realloc(*b, cap * sizeof(int));
            if (!b_r) {
                free(b);
                return INVALID_MEMORY;
            }
            *b = b_r;
        }
    }
    return OK;
}

int is_primary(long int a) {
    a = (a < 0) ? -a : a;
    if (a == 2) {
        return 0;
    }
    if (a == 1  || a == 0) {
        return 2;
    }
    if (a % 2 == 0) return 1;
    for (int i = 3; i < a / 2 + 1; i += 2) {
        if (a % i == 0) return 1;
    }
    return 0;
}

enum errors fac(long int a, unsigned long long int* result) {
    *result = 1;
    for (int i = 2; i <= a; i++) {
        if (*result > ULLONG_MAX / i) return INVALID_MEMORY;
        *result *= i;
    }
    return OK;
}

enum errors sum_num(long int a, unsigned long long int* result) {
    *result = 1;
    if (a <= 0) return INVALID_INPUT;
    for (int i = 2; i <= a; i++) {
        if (*result + i > ULLONG_MAX) return INVALID_MEMORY;
        *result += i;
    }
    return OK;
}

enum errors degree(long int a, int n, long int** result) {
    *result = (long int*)malloc(a * sizeof(long int));
    if (!*result) return INVALID_MEMORY;
    for (int i = 1; i <= a; i++) {
        (*result)[i - 1] = pow(n, i);
    }
    return OK;
}

enum errors to_16(long int a, char** result, int* kol) {
    int cap = 4;
    *result = (char*)malloc(sizeof(char) * cap);
    if (!*result) return INVALID_MEMORY;
    int temp = 0;
    while (a > 0) {
        temp = a % 16;
        if (temp < 10) {
            (*result)[(*kol)++] = temp + '0';
        }
        else {
            (*result)[(*kol)++] = temp - 10 + 'A';
        }
        a /= 16;
        if (cap == *kol) {
            cap *= 2;
            char* f_r = (char*)realloc(*result, sizeof(char) * cap);
            if (!*f_r) return INVALID_MEMORY;
            *result = f_r;
        }
    }
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Неверное количество аргументов\n");
        return INVALID_INPUT;
    }

    char* endptr;
    int res;
    if (sscanf(argv[1], "%d", &res) == 0) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    if (!(argv[2][0] == '/' || argv[2][0] == '-') || argv[2][2] != '\0') {
        printf("Неверный ввод аргументов\n");
        return INVALID_INPUT;
    }

    switch (argv[2][1]) {
        case 'h': {
            int* result = NULL;
            int kol = 0;
            enum errors status = numbers(res, &result, &kol);
            if (status == OK && result != NULL) {
                for (int i = 0; i < kol; i++) {
                    printf("%d ", result[i]);
                }
                printf("\n");
            }
            else if (status == 1) {
                printf("Положительное число требуется\n");
                return INVALID_INPUT;
            }
            else {
                printf("Ошибка выделения памяти\n");
                return INVALID_MEMORY;
            }
            if (result == NULL) {
                printf("Таких чисел нет\n");
                free(result);
            }
            break;
        }

        case 'p': {
            int pr = is_primary(res);
            if (pr == 2) {
                printf("Число Никакое\n");
            }
            else  if(pr){
                printf("Число составное\n");
            }
            else {
                printf("Число простое\n");
            }
            break;
        }

        case 's': {
            int kol = 0;
            char* res_s = NULL;
            if (to_16(res, &res_s, &kol) == OK) {
                for (int i = kol - 1; i >= 0; i--) {
                    printf("%c ", res_s[i]);
                }
            }
            else {
                printf("Ошибка выделения памяти\n");
                return INVALID_MEMORY;

            }
            printf("\n");
            if(!res_s) free(res_s);
            break;
        }
        case 'e': {
            if (res > 10 || res < 0) {
                printf("Число должно быть не больше 10 и не меньше 1\n");
                return INVALID_INPUT;
            }
            int osnov = 1;
            while (osnov != 11) {
                long int* resu = NULL;
                if (degree(res, osnov, &resu) == OK) {
                    for (int i = 0; i < res; i++) {
                        printf("%lu ", resu[i]);
                    }
                    printf("\n");
                }
                else {
                    printf("Ошибка выделения памяти\n");
                    return INVALID_MEMORY;
                }
                osnov++;
                if(!resu) free(resu);
            }
            break;
        }
        case 'a': {
            unsigned long long int res_a = 1;
            if (sum_num(res, &res_a) != OK) {
                printf("Ошибка при расчёте суммы\n");
            }
            else {
                printf("%llu\n", res_a);
            }
            break;
        }

        case 'f': {
            if (res < 0) {
                printf("Только положительные числа для факториала\n");
                return INVALID_INPUT;
            }
            unsigned long long int res_f = 1;
            if (fac(res, &res_f) != OK) {
                printf("Переполнение\n");
                return INVALID_MEMORY;
            }
            else {
                printf("%llu\n", res_f);
            }
            break;
        }

        default:
            printf("Неверный параметр\n");
            break;
    }

    return 0;
}

