#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_N_NAME_FILE 100

enum errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    INVALID_FILE
};

void count_bukv(FILE* input, FILE* output){
    int c;
    long int count_str = 1, count_bukv = 0;
    while(!feof(input)){
        c = fgetc(input);
        if (c == EOF){
            fprintf(output, "В %ld строке: %ld\n", count_str, count_bukv);
        }
        if(c == '\n'){
            fprintf(output, "В %ld строке: %ld\n", count_str, count_bukv);
            count_str += 1;
            count_bukv = 0;
        }
        else if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
            count_bukv++;
        }
    }
}

void count_ne_bukv(FILE* input, FILE* output){
    int c;
    long int count_str = 1, count_bukv = 0;
    while(!feof(input)){
        c = fgetc(input);
        if (c == EOF){
            fprintf(output, "В %ld строке: %ld\n", count_str, count_bukv);
        }
        if(c == '\n'){
            fprintf(output, "В %ld строке: %ld\n", count_str, count_bukv);
            count_str += 1;
            count_bukv = 0;
        }
        else if(!isalnum(c) || c == ' '){
            count_bukv++;
        }
    }
}

void asci(FILE* input, FILE* output){
    int c;
    while(!feof(input)){
        c = fgetc(input);
        if(c >= '0' && c <= '9'){
            fputc(c, output);
        }
        else{
            fprintf(output, "%X", c);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Некорректный ввод\n");
        return INVALID_INPUT;
    }
    if (!((argv[1][0] == '-' || argv[1][0] == '/') && (strlen(argv[1]) == 2
    || (strlen(argv[1]) == 3 && argv[1][1] == 'n')))) {
        printf("Некорректный флаг\n");
        return INVALID_INPUT;
    }

    char* input_file_path = argv[2];
    char* out_file = (char*)malloc(MAX_N_NAME_FILE * sizeof(char));

    if (!out_file) {
        printf("Ошибка памяти\n");
        return INVALID_MEMORY;
    }
    int n_flag = argv[1][1] == 'n';

    if (n_flag) {
        if (argc < 4) {
            printf("Выходной файл не указан\n");
            free(out_file);
            return INVALID_INPUT;
        }
        strcat(out_file, argv[3]);
        const char *file_name_in = strrchr(input_file_path, '/');
        if (file_name_in) {
            file_name_in++;
        } else {
            file_name_in = input_file_path;
        }
        const char *file_name_out = strrchr(argv[3], '/');
        if (file_name_out) {
            file_name_out++;
        } else {
            file_name_out = out_file;
        }
        //printf("%s %s\n", file_name_out, file_name_in);
        if(strcmp(file_name_in, file_name_out) == 0){
            printf("Одинаковые файлы нельзя\n");
            return INVALID_INPUT;
        }
    } else {
        const char *file_name = strrchr(input_file_path, '/');
        if (file_name) {
            file_name++;
        } else {
            file_name = input_file_path;
        }

        strcpy(out_file, "out_");
        strcat(out_file, file_name);

    }

    FILE* input_file = fopen(input_file_path, "r");
    FILE* output_file = fopen(out_file, "w");

    if (!input_file || !output_file) {
        printf("Не удалось открыть файлы\n");
        if (input_file) fclose(input_file);
        if (output_file) fclose(output_file);
        free(out_file);
        return INVALID_FILE;
    }
    char flag_action = n_flag ? argv[1][2] : argv[1][1];
    switch (flag_action) {
        case 'd': {
            int symbol;
            while ((symbol = fgetc(input_file)) != EOF) {
                if (symbol >= '0' && symbol <= '9') continue;
                fputc(symbol, output_file);
            }
            printf("Убрали арабские цифры\n");
            break;
        }
        case 'i':{//сколько раз буквы латинского алфавита
            count_bukv(input_file, output_file);
            printf("Буквы посчитаны\n");
            break;
        }
        case 's':{//сколько раз символы отличные от латиницы, цифр, пробелов
            count_ne_bukv(input_file, output_file);
            printf("Посчитали не буквы, не цифры\n");
            break;
        }
        case 'a':{//символы не цифры в аски код в 16 систему счисления
            asci(input_file, output_file);
            printf("Заменили не цифры на аски-код\n");
            break;
        }
        default:
            printf("Неизвестный флаг: %c\n", flag_action);
            fclose(input_file);
            fclose(output_file);
            free(out_file);
            return INVALID_INPUT;
    }
    fclose(input_file);
    fclose(output_file);
    free(out_file);

    return OK;
}
