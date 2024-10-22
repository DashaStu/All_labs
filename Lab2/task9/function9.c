#include "task9.h"

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

enum errors prime_factors(int n, int** factors, int* size) {
    (*factors) = (int*)malloc(n * sizeof(int)); // Исправлено с double на int
    if ((*factors) == NULL) {
        return INVALID_MEMORY;
    }
    int i = 2;
    *size = 0;
    while (n % i == 0) {
        (*factors)[(*size)++] = i;
        n /= i;
    }
    for (i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            (*factors)[(*size)++] = i;
            n /= i;
        }
    }
    if (n > 2) {
        (*factors)[(*size)++] = n;
    }
    return OK;
}

enum errors drob(double** result, int* len, int count, int base, ...) {
    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }
    (*result) = (double*)malloc(count * sizeof(double));
    if ((*result) == NULL) {
        return INVALID_MEMORY;
    }


    va_list temp;
    va_start(temp, base);

    *len = 0;  // Инициализация длины
    int* factor = NULL;
    int size = 0;

    for (int i = 0; i < count; i++) {
        double tek = va_arg(temp, double);
        double kop_tek = tek;
        if (tek < EPSILON || tek > 1 - EPSILON) {
            continue;
        }

        int znam = 1;
        int chis = 1;

        // Переводим дробь в форму p/q (числитель/знаменатель)
        while (fabs(tek - floor(tek)) > EPSILON) {
            znam *= 10;
            tek *= 10;
        }
        chis = (int)tek;
        //printf("%d %d\n", chis, znam);

        // Сокращаем дробь
        int gcd_znam = gcd(chis, znam);
        if (gcd_znam != 1) {
            znam /= gcd_znam;
        }
        // Разложим основание на простые множители
        if(prime_factors(base, &factor, &size) == INVALID_MEMORY){
            return INVALID_MEMORY;
        }

        // Убираем простые множители основания из знаменателя
        for (int j = 0; j < size; j++) {
            while (znam % factor[j] == 0) {
                //printf("%d ", znam);
                znam /= factor[j];
            }
        }
        // Если знаменатель сократился до 1, то дробь конечная
        if (znam == 1) {
            (*result)[(*len)++] = kop_tek;
        }
    }

    free(factor);
    va_end(temp);

    return OK;
}