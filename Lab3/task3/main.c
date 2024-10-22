#include "task3.h"

int main(int argc, char* argv[]){
    if(argc < 4){
        printf("Invalid input, you forgot something\n");
        return INVALID_INPUT;
    }
    if(check_file(argv[1], argv[3]) != OK ){
        printf("Invalid input file\n");
        return INVALID_INPUT;
    }
    if(!((argv[2][0] == '-' || argv[2][0] == '/') && argv[2][2] == '\0')){
        printf("Invalid input flag\n");
        return INVALID_INPUT;
    }
    FILE* file_in = fopen(argv[1], "r");
    FILE * file_out = fopen(argv[3], "w");
    if( file_in == NULL || file_out == NULL){
        printf("Files dosent open\n");
        if(file_out != NULL) fclose(file_out);
        if(file_in != NULL) fclose(file_in);
        return INVALID_FILE;
    }
    struct Employee* array;
    int len;
    enum errors res_file = file_to_array(&array, file_in, &len);
    if(res_file == INVALID_INPUT){
        printf("Invalid input in file\n");
        free(array);
        fclose(file_in);
        fclose(file_out);
        return INVALID_INPUT;
    }
    else if(res_file == INVALID_MEMORY){
        printf("Invalid memory\n");
        free(array);
        fclose(file_in);
        fclose(file_out);
        return INVALID_MEMORY;
    }
    switch(argv[2][1]){
        case 'a':{
            qsort(array, len, sizeof(struct Employee), compare_a);
            write_to_file(file_out, array, len);
            free(array);
            printf("Complete\n");
            break;
        }
        case'd':{
            qsort(array, len, sizeof(struct Employee), compare_d);
            write_to_file(file_out, array, len);
            free(array);
            printf("Complete\n");
            break;
        }
        default:{
            printf("Not such flag\n");
            break;
        }
    }
    fclose(file_in);
    fclose(file_out);
}
