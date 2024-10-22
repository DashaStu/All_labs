#include "task9.h"

int main(){
    double* result = NULL;
    int len;
    enum errors res_funk = drob(&result, &len, 5, 8, 0.5, 0.333, 0.275, 0.25, 0.67);
    if(res_funk == OK){
        if(len != 0){
            for(int i = 0;i<len;i++){
                printf("%lf ", result[i]);
            }
            printf("\n");
        }
        else{
            printf("we have not numbers\n");
        }
        if(result != NULL) free(result);
    }
    else if(res_funk == INVALID_INPUT){
        printf("Invalid input\n");
    }
    else{
        if(result != NULL) free(result);
        printf("Invalid memory\n");
    }
    return 0;
}