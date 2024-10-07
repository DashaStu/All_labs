#include "task1.h"

int main(int argc, char* argv[]) {
    if(argc < 3 || argv[1][0] != '-'){
        printf("Ivalid input\n");
        return INVALID_INPUT;
    }
    char* result = NULL;
    switch(argv[1][1]){
        case 'l':{
            if(argc != 3)
            {
                printf("Invalid input\n");
                return INVALID_INPUT;
            }
            printf("%d\n", len_str(argv[2]));
            break;
        }
        case 'r':{
            if(argc != 3)
            {
                printf("invalid input\n");
                return INVALID_INPUT;
            }

            if(reverse_str(argv[2],&result ) != OK){
                printf("Invalid memory\n");
                if(result != NULL) free(result);
                return INVALID_MEMORY;
            }
            printf("%s\n", result);
            break;
        }
        case 'u':{
            if(argc != 3)
            {
                printf("invalid input\n");
                return INVALID_INPUT;
            }
            if(up_str(argv[2], &result) != OK){
                printf("Invalid memory\n");
                if(result != NULL) free(result);
                return INVALID_MEMORY;
            }
            printf("%s\n", result);
            break;
        }
        case 'n':{
            if(argc != 3)
            {
                printf("invalid input\n");
                return INVALID_INPUT;
            }

            if(str_swap_symbol(argv[2], &result) != OK){
                printf("Invalid memory\n");
                if(result != NULL) free(result);
                return INVALID_MEMORY;
            }
            printf("%s\n", result);
            break;
        }
        case 'c':{
            int count_str = argc - 3;
            if(count_str == 0){
                printf("Invalid input\n");
                return INVALID_INPUT;
            }
            unsigned int seed;
            if(str_to_u_int(argv[2], &seed) != OK){
                printf("Invalid input\n");
                return INVALID_INPUT;
            }
            if(str_con(count_str, (argv+3), &result, seed) != OK){
                printf("Invalid memory\n");
                if(result != NULL) free(result);
                return INVALID_MEMORY;
            }
            printf("%s\n", result);
            break;
        }
        default:{
            printf("Not such flag\n");
            return INVALID_INPUT;
        }

    }
    if(result != NULL) free(result);
    return 0;
}
