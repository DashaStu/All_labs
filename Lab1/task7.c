#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_BUF_SIZE 101

enum errors {
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    INVALID_FILE
};

enum errors read_input_from_file_into_array(FILE** input, char** buff, int* len)
{
    *len = 0;

    char symbol = fgetc(*input);
    while (symbol == ' ' || symbol == '\t' || symbol == '\n' || symbol == '\r')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != '\r' && symbol != EOF)
    {
        (*buff)[(*len)++] = symbol;
        if (*len == MAX_BUF_SIZE + 1)
        {
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    (*buff)[(*len)] = '\0';
    return OK;


}

void convert_to_lowercase_and_base4(char** array, const int len, short** result)
{
    short number_base4 = 0;
    for (int i = 0; i < len; ++i)
    {
        if (isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
        int temp_num = (int)(*array)[i];
        int base10 = 1;
        while (temp_num > 0)
        {
            number_base4 += (temp_num % 4) * base10;
            base10 *= 10;
            temp_num /= 4;
        }
        (*result)[i] = number_base4;
        number_base4 = 0;
    }
}

void convert_to_lowercase(char** array, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
    }
}

void convert_to_ascii_base8(char** array, int len, short** result)
{
    short number_base8 = 0;
    for (int i = 0; i < len; ++i)
    {
        short temp_num = (short)(*array)[i];
        int base10 = 1;
        while (temp_num > 0)
        {
            number_base8 += (temp_num % 8) * base10;
            base10 *= 10;
            temp_num /= 8;
        }
        (*result)[i] = number_base8;
        number_base8 = 0;
    }
}

enum errors valid_file(char* input, char* output){
    char* index_in = strrchr(input, '/');
    char* name_in; char* name_out;
    if(index_in) {
        index_in++;
        name_in = index_in;
    }
    else name_in = input;
    char* index_out = strrchr(output, '/');
    if(index_out) {
        index_out++;
        name_out = index_out;
    }
    else name_out = output;
    //printf("%s %s\n",name_in, name_out);
    if (strcmp(name_in, name_out) == 0) return INVALID_INPUT;
    return OK;
}

int main(int argc, char* argv[]) {
    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0')) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    switch (argv[1][1]) {
        case 'r': {
            if (argc != 5) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }

            if(valid_file(argv[2], argv[3]) != OK || valid_file(argv[2], argv[4]) != OK ||
               valid_file(argv[3], argv[4]) != OK){
                printf("Нельзя одинаковые файлы\n");
                return INVALID_INPUT;
            }
            FILE* f1 = fopen(argv[2], "r");
            FILE* f2 = fopen(argv[3], "r");
            FILE* f3 = fopen(argv[4], "w");
            if (f1 == NULL || f2 == NULL || f3 == NULL)
            {
                printf("Ошибка открытия файла(ов)\n");
                if (f1 != NULL) fclose(f1);
                if (f2 != NULL) fclose(f2);
                if (f3 != NULL) fclose(f3);
                return INVALID_FILE;
            }
            char* buff;
            buff = (char*)malloc(MAX_BUF_SIZE * sizeof(char));
            if (buff == NULL)
            {
                printf("Ошибка выделения памяти\n");
                fclose(f1);
                fclose(f2);
                fclose(f3);
                return INVALID_MEMORY;
            }

            int len_r = 0;
            while (!feof(f1) && !feof(f2))
            {
                if (read_input_from_file_into_array(&f1, &buff, &len_r) != OK)
                {
                    printf("Много букв\n");
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f3 != NULL) fclose(f3);
                    if(buff!= NULL) free(buff);
                    return INVALID_INPUT;
                }
                if (len_r > 0) fprintf(f3, "%s ", buff);

                if (read_input_from_file_into_array(&f2, &buff, &len_r) != OK)
                {
                    printf("Много букв\n");
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f3 != NULL) fclose(f3);
                    if(buff!= NULL) free(buff);
                    return INVALID_INPUT;
                }
                if (len_r > 0) fprintf(f3, "%s ", buff);
            }
            while (!feof(f1))
            {
                if (read_input_from_file_into_array(&f1, &buff, &len_r) != OK)
                {
                    printf("Много букв\n");
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f3 != NULL) fclose(f3);
                    if(buff!= NULL) free(buff);
                    return INVALID_INPUT;
                }
                if (len_r > 0) fprintf(f3, "%s ", buff);
            }
            while (!feof(f2))
            {
                if (read_input_from_file_into_array(&f2, &buff, &len_r) != OK)
                {
                    printf("Много букв\n");
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f3 != NULL) fclose(f3);
                    if(buff!= NULL) free(buff);
                    return INVALID_INPUT;
                }
                if (len_r > 0) fprintf(f3, "%s ", buff);
            }
            printf("Конец программы r\n");
            if (f1 != NULL) fclose(f1);
            if (f2 != NULL) fclose(f2);
            if (f3 != NULL) fclose(f3);
            if(buff!= NULL) free(buff);
            break;
        }
        case 'a': {
            if (argc != 4) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            if(valid_file(argv[2], argv[3]) != OK){
                printf("Одинаковые файлы нельзя\n");
                return INVALID_INPUT;
            }

            FILE* input = fopen(argv[2], "r");
            FILE* output_a = fopen(argv[3], "w");
            if (input == NULL || output_a == NULL){
                if(input != NULL) fclose(input);
                if(output_a != NULL) fclose(output_a);
                printf("Invalid file\n");
                return INVALID_FILE;
            }
            char* buffer;
            short* result;
            buffer = (char*)malloc(MAX_BUF_SIZE * sizeof(char));
            result = (short*)malloc(MAX_BUF_SIZE * sizeof(short));

            if (buffer == NULL || result == NULL)
            {
                printf("Оибка выделения памяти\n");
                fclose(input);
                fclose(output_a);
                if(buffer!= NULL) free(buffer);
                if(result!= NULL)free(result);
                return INVALID_MEMORY;
            }
            int len = 0;
            int count_token = 0;
            while (!feof(input))
            {
                if (read_input_from_file_into_array(&input, &buffer, &len) != OK)
                {
                    printf("Много букв\n");
                    if (input != NULL) fclose(input);
                    if (output_a != NULL) fclose(output_a);
                    if(buffer!= NULL) free(buffer);
                    if(result!= NULL)free(result);
                    return INVALID_INPUT;
                }
                count_token++;
                if (len > 0 && count_token % 10 == 0)
                {
                    convert_to_lowercase_and_base4(&buffer, len, &result);
                    for (int i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else if (len > 0 && count_token % 2 == 0)
                {
                    convert_to_lowercase(&buffer, len);
                    fprintf(output_a, "%s ", buffer);
                }
                else if (len > 0 && count_token % 5 == 0)
                {
                    convert_to_ascii_base8(&buffer, len, &result);
                    for (int i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else
                {
                    fprintf(output_a, "%s ", buffer);
                }
            }
            printf("Конец программы a\n");
            if (input != NULL) fclose(input);
            if (output_a != NULL) fclose(output_a);
            if(buffer!= NULL) free(buffer);
            if(result!= NULL)free(result);
            break;
        }
        default: {
            printf("Нет такого флага\n");
            return INVALID_INPUT;
        }
    }
    return 0;
}