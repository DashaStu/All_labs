#include "task1.h"

int len_str(const char* str){
    int i = 0;
    for(;*str++ != '\0';++i){}
    return i;
}
enum errors reverse_str(const char* str, char** result){
    int size_s = len_str(str);
    (*result) = (char*)malloc((size_s+ 1) * sizeof(char));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    for(int i = 0; i< size_s;i++){
        (*result)[i] = str[size_s - i - 1];
    }
    (*result)[size_s] = '\0';
    return OK;
}

enum errors up_str(const char* str, char** result){
    int size_s = len_str(str);
    (*result) = (char*)malloc((size_s+1) * sizeof(char));
    if((*result) == NULL){
        return INVALID_MEMORY;
    }
    for(int i = 0; i < size_s; i++){
        if(i % 2 == 1 && !(str[i] >= 'A' && str[i] <= 'Z') && (str[i] >= 'a' && str[i] <= 'z')){
            (*result)[i] = str[i] - 32;
        }
        else{
            (*result)[i] = str[i];
        }
    }
    (*result)[size_s] = '\0';
    return OK;
}

enum errors str_swap_symbol(const char* str, char** result){
    int size_s = len_str(str);
    (*result) = (char*)malloc((size_s+1) * sizeof(char));
    if((*result) == NULL){
        return INVALID_MEMORY;
    }
    int index = 0;
    for(int i =0;i<size_s;i++){
        if(str[i] >= '0' && str[i] <= '9'){
            (*result)[index++] = str[i];
        }
    }
    for(int i =0;i<size_s;i++){
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')){
            (*result)[index++] = str[i];
        }
    }
    for(int i =0;i<size_s;i++){
        if(!(str[i] >= '0' && str[i] <= '9') &&
           !((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))){
            (*result)[index++] = str[i];
        }
    }
    (*result)[size_s] = '\0';
    return OK;
}

enum errors str_to_u_int(const char* str, unsigned int* result){
    if(len_str(str) > 10) return INVALID_INPUT;
    if(str[0] == '-') return INVALID_INPUT;
    for(int i = 0; i< len_str(str);i++){
        if(!(str[i] >= '0' && str[i] <= '9')){
            return INVALID_INPUT;
        }
    }
    sscanf(str, "%u", result);
    return OK;
}

void contation(char* str, char ** result, int* len){
    for(int i = 0;str[i] != '\0'; i++){
        (*result)[(*len)++] = str[i];
    }
    (*result)[(*len)] = '\0';
}

enum errors str_con(int count_str, char** str, char** result, unsigned int seed){
    int len, cap = 0;
    for(int i = 0; i< count_str; i++){
        len = len_str(str[i]);
        if(len>cap) cap = len;
    }
    cap *= count_str;
    len = 0;
    (*result) = (char*)malloc(cap * sizeof(char));
    if((*result) == NULL) return INVALID_MEMORY;
    srand(seed);
    for(int i = 0; i < count_str; i++){
        int number = rand() % count_str;
        //printf("%d ",number);
        contation(str[number], result, &len);
    }
    return OK;
}