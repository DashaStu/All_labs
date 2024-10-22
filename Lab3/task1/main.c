#include "task1.h"

int main(){
    char* result = NULL;
    enum errors res_funk = to_2r(10,1, &result);
    //255 -> FF(16), 10 -> 1010(2), 18 -> 12(16), 399 -> CF(32)
    if(res_funk == OK){
        printf("%s\n", result);
        free(result);
    }
    else if(res_funk == INVALID_MEMORY){
        printf("Invalid memory\n");
        if (result != NULL) free(result);
        return INVALID_MEMORY;
    }
    else{
        printf("Invslid input\n");
        free(result);
        return INVALID_INPUT;
    }
}