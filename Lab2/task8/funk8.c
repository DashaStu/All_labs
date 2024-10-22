#include "task8.h"

enum errors sum_num(char** result, int base, char* num1, char* num2){
    int l1 = strlen(num1);
    int l2 = strlen(num2);
    int i, sum, stack = 0;
    int max_len = l1 > l2? l1:l2;
    (*result) = (char*)malloc((max_len + 2) * sizeof(char));
    if(*result == NULL) return INVALID_MEMORY;
    (*result)[max_len + 1] = '\0';
    for(i = 0;i<max_len;i++){
        int i1 = l1 - 1 - i;
        int i2 = l2 - 1 - i;
        int d1 = i1 >= 0 ? (isdigit(num1[i1]) ? num1[i1] - '0' : num1[i1] - 'A' + 10) : 0;
        int d2 = i2 >= 0 ? (isdigit(num2[i2]) ? num2[i2] - '0' : num2[i2] - 'A' + 10) : 0;
        sum = d1 + d2 + stack;
        stack = sum / base;
        (*result)[max_len - i] = sum % base < 10 ? (sum % (base)) + '0': (sum % base) - 10 + 'A';
        //printf("%d %d %d %c\n",d1, d2,sum, (*result)[max_len - i]);
    }
    if(stack > 0)
        (*result)[0] = stack < 10 ? stack + '0': stack - 10 + 'A';
    else
        memmove(*result, *result + 1, max_len + 1);

    return OK;
}

enum errors sum_numbers(char** result, int base, int count, ...){
    if(base < 2 || base > 36 || count <= 0){
        return INVALID_INPUT;
    }
    va_list(temp);
    va_start(temp, count);
    char* num1 = va_arg(temp, char*);
    if(sum_num(result, base, "0", num1) == INVALID_MEMORY){
        return INVALID_MEMORY;
    }
    for(int i =0;i<count - 1; i++){
        char* num2 = va_arg(temp, char*);
        char* old = (char*)malloc((strlen(*result) + 1) * sizeof(char));
        if(old == NULL) return INVALID_MEMORY;
        strcpy(old, *result);
        if(sum_num(result, base, num2, old) == INVALID_MEMORY){
            free(old);
            return INVALID_MEMORY;
        }
        free(old);
    }
    va_end(temp);
    return OK;
}

void first_0(char** result){
    int i = 0;
    while((*result)[i] == '0' && i != strlen(*result) - 1){
        i++;
    }
    memmove(*result, *result + i, strlen(*result));
}