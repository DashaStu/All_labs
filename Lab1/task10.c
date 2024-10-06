#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

enum errors {
    INVALID_INPUT,
    OK,
    INVALID_MEMORY
};

enum errors str_to_ll(const char *str, long long int* a, int base) {
    char* endptr;
    *a = strtoll(str, &endptr, base);
    if (*a == LLONG_MAX || *a == LLONG_MIN) return INVALID_INPUT;
    return OK;
}

enum errors check_number(char* number, int base)
{
    for (int i = 0; number[i] != '\0'; ++i)
    {
        if (number[0] == '-') continue;
        else if ((number[i] >= '0' && number[i] <= '9') && (number[i] - '0') < base);
        else if ((number[i] >= 'A' && number[i] <= 'Z') && (number[i] - 55) < base);
        else return INVALID_INPUT;
    }

    return OK;
}
enum errors tobase(char** result, long long int number, int base, char* buk) {
    int cap = 20;
    (*result) = (char*)malloc(sizeof(char) * cap);
    if (*result == NULL) return INVALID_MEMORY;

    int i = 0;
    int flag_negitive = 0;
    if (number < 0)
    {
        (*result)[0] = '-';
        number *= -1;
        ++i;
        flag_negitive = 1;
    }

    while (number > 0)
    {
        int temp = number % base;
        if (temp >= base)
        {
            free(result);
            return INVALID_INPUT;
        }
        number /= base;
        (*result)[i++] = (char)buk[temp];
        if (i == cap)
        {
            char** for_realloc = NULL;
            cap *= 2;
            for_realloc = (char**)realloc(result, cap);
            if (for_realloc == NULL)
            {
                free(result);
                return INVALID_MEMORY;
            }
            result = for_realloc;
        }
    }

    int start = flag_negitive ? 1 : 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = (*result)[start];
        (*result)[start] = (*result)[end];
        (*result)[end] = temp;
        start++;
        end--;
    }

    (*result)[i] = '\0';
    return OK;
}

int main() {
    int s_s;
    if (scanf("%d", &s_s) != 1) {
        printf("Ошибка ввода\n");
        return INVALID_INPUT;
    }
    if (!(s_s >= 2 && s_s <= 36)) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    long long int result = 0;
    long long int number = 0;
    char* end_input = "Stop";
    int flag = 1;
    char* input_number = NULL;
    input_number = (char*)malloc(sizeof(char) * 101);
    if (input_number == NULL) {
        printf("Ошибка выделения памяти\n");
        return INVALID_MEMORY;
    }
    char* buk = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (scanf("%100s", input_number)) {
        if (strcmp(end_input, input_number) == 0) {
            if (result != 0)
            {
                int* base = (int*)malloc(5 * sizeof(int));
                char* result_number = NULL;
                if (base == NULL) {
                    printf("Ошибка выделения памяти\n");
                    return INVALID_MEMORY;
                }
                base[0] = s_s;
                base[1] = 9;
                base[2] = 18;
                base[3] = 27;
                base[4] = 36;
                for (int i = 0; i < 5; i++) {
                    if (tobase(&result_number, result, base[i], buk) != OK) {
                        printf("ОШИБКА памяти\n");
                        free(base);
                        free(result_number);
                        return	INVALID_MEMORY;
                    }
                    printf("В %d системе счисления: %s\n", base[i], result_number);
                    if(!result_number) free(result_number);
                    result_number = NULL;
                }
                free(base);
                break;
            }
            else {
                printf("Вы не ввели чисел(\n");
                return INVALID_INPUT;
            }
        }
        if (check_number(input_number, s_s) != OK) {
            printf("Число инвалидное %s\n", input_number);
            return INVALID_INPUT;
        }
        if (str_to_ll(input_number, &number, s_s) == INVALID_INPUT) {
            printf("Некорректный ввод\n");
            return INVALID_INPUT;
        }
        if (llabs(number) - llabs(result) > 0) {
            result = number;

        }
    }

}
