#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

enum errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    INVALID_FILE
};
enum errors convert_str_to_ll_int(const char* str, long long int* result, int base)
{
    char* endptr;
    *result = strtoll(str, &endptr, base);

    if (*result == LLONG_MAX || *result == LLONG_MIN)
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

enum errors read_input_from_file_into_array(FILE** input, char** buff, int* len, int* min_base, int* capacity)
{
    *len = 0;
    *min_base = 2;
    char symbol = fgetc(*input);
    int flag_negative = 0;
    int flag_skip = 0;
    while (symbol == ' ' || symbol == '\t' || symbol == '\n')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != EOF)
    {
        if (symbol == '-' && *len == 0)
        {
            (*buff)[(*len)++] = symbol;
            flag_negative = 1;
        }
        else if ((symbol == '0' && *len == 0) || (symbol == '0' && *len == 1 && flag_negative == 1))
        {
            symbol = fgetc(*input);
            flag_skip = 1;
            continue;
        }
        else if (isdigit(symbol))
        {
            (*buff)[(*len)++] = symbol;
            if (symbol - '0' + 1 > *min_base)
            {
                *min_base = symbol - '0' + 1;
            }
        }
        else if (isalpha(symbol))
        {
            (*buff)[(*len)++] = (char)toupper(symbol);
            if (toupper(symbol) - 'A' + 10 + 1 > *min_base)
            {
                *min_base = toupper(symbol) - 'A' + 10 + 1;
            }
        }
        else
        {
            return INVALID_INPUT;
        }
        if (*len == *capacity)
        {
            *capacity *= 2;
            char* for_realloc = (char*)realloc(*buff, *capacity);
            if (for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *buff = for_realloc;
        }
        if (*min_base > 36)
        {
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    if (*len == 0 && flag_skip && flag_negative == 0) (*buff)[(*len)++] = '0';
    if (*len == 1 && flag_skip && flag_negative) (*buff)[(*len)++] = '0';
    (*buff)[(*len)] = '\0';
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    if(strcmp(argv[1], argv[2]) == 0){
        printf("ТАк нельзя\n");
        return INVALID_INPUT;
    }
    FILE* f1 = fopen(argv[1], "r");
    FILE* f2 = fopen(argv[2], "w");
    if (f1 == NULL || f2 == NULL) {
        printf("Не открываются файлы\n");
        if(f1 != NULL) fclose(f1);
        if(f2 != NULL) fclose(f2);
        return INVALID_FILE;
    }
    int capacity = 2;
    char* buffer = (char*)malloc(capacity * sizeof(char));
    if (buffer == NULL)
    {
        printf("Ошибка: ошибка при выделении памяти");
        return INVALID_MEMORY;
    }

    int len = 0;
    int min_base = 2;

    while (!feof(f1))
    {
        enum errors err = read_input_from_file_into_array(&f1, &buffer, &len, &min_base, &capacity);
        if (err == INVALID_INPUT)
        {
            if (f1 != NULL) fclose(f1);
            if (f2 != NULL) fclose(f2);
            if(buffer != NULL) free(buffer);
            printf("некорректные данные в файле\ngcc");
            return INVALID_INPUT;
        }
        else if (err == INVALID_MEMORY)
        {
            if(buffer != NULL) free(buffer);
            printf("INVALID_MEMORY\n");
            if (f1 != NULL) fclose(f1);
            if (f2 != NULL) fclose(f2);
            return INVALID_MEMORY;
        }
        if (len > 0)
        {
            long long int number_base10 = 0;
            if (convert_str_to_ll_int(buffer, &number_base10, min_base) != OK)
            {
                if (f1 != NULL) fclose(f1);
                if (f2 != NULL) fclose(f2);
                free(buffer);
                return INVALID_INPUT;
            }
            fprintf(f2, "входное число: %s\n", buffer);
            fprintf(f2, "минимальное основание: %d\n", min_base);
            fprintf(f2, "число в 10 сс: %lld\n", number_base10);
            fprintf(f2, "\n");
        }
    }

    printf("Конец программы\n");
    if (f1 != NULL) fclose(f1);
    if (f2 != NULL) fclose(f2);
    free(buffer);

    return 0;
}