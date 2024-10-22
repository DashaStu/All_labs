#include "task8.h"

int main(){
    char* result = NULL;
    enum errors res_funk = sum_numbers(&result, 10, 2, "00000000", "100", "30", "40", "20");
    if(res_funk == OK){
        first_0(&result);
        printf("%s\n", result);
        free(result);
    }
    else if(res_funk == INVALID_MEMORY){
        printf("Invalid memory\n");
        if(result!= NULL) free(result);
        return INVALID_MEMORY;
    }
    else{
        printf("Invalid input\n");

        return INVALID_INPUT;
    }


    return OK;
}