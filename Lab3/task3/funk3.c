#include "task3.h"

enum errors check_file(char* f1, char* f2){
    char* name_in = strrchr(f1, '/');
    if(name_in){
        name_in++;
    }
    else{
        name_in = f1;
    }
    char* name_out = strrchr(f2, '/');
    if(name_out){
        name_out++;
    }
    else{
        name_out = f2;
    }
    //printf("%s %s\n", name_out, name_in);
    if(strcmp(name_in, name_out) == 0){
        return INVALID_FILE;
    }
    return OK;
}

enum errors check_name(char*str){
    for(int i = 0; i < strlen(str); i++){
        if(!((str[i] >='a' && str[i]<='z') || (str[i]>='A' && str[i] <='Z'))){
            return INVALID_INPUT;
        }
    }
    return OK;
}

enum errors file_to_array(struct Employee** result, FILE* file_in, int* len){
    int capacity = 2;
    *len = 0;
    (*result) = (struct Employee*)malloc(capacity * sizeof(struct Employee));
    if((*result) == NULL){
        return INVALID_MEMORY;
    }
    int check;
    while((check = fscanf(file_in, "%d:%[^:]:%[^:]:%lf\n", &(*result)[*len].id, (*result)[*len].firstname, (*result)[*len].surname, &(*result)[*len].salary)) == 4){
        if(check_name((*result)[*len].surname) != OK || check_name((*result)[*len].firstname) != OK){
            printf("name\n");
            return INVALID_INPUT;
        }
        if((*result)[*len].id < 0 || (*result)[*len].salary < 0){
            printf("id\n");
            return INVALID_INPUT;
        }
        (*len) += 1;
        if((*len) == capacity){
            capacity *= 2;
            struct Employee* new_place = (struct Employee*)realloc((*result),capacity * sizeof(struct Employee));
            if(new_place == NULL){
                free(*result);
                return INVALID_MEMORY;
            }
            (*result) = new_place;
        }
    }
    if(check < 4 && check > 0){
        return INVALID_INPUT;
    }
    return OK;
}

int compare_a(const void* a,const void* b){
    struct Employee* Ea = (struct Employee*)a;
    struct Employee* Eb = (struct Employee*)b;
    if(Ea->salary - Eb->salary > EPSILON) return 1;
    if(Eb->salary - Ea->salary > EPSILON) return -1;
    int str_com = strcmp(Ea->surname, Eb->surname);
    if(str_com != 0) return str_com;
    str_com = strcmp(Ea->firstname, Eb->firstname);
    if(str_com != 0) return str_com;
    return Ea->id - Eb->id;
}

int compare_d(const void* a,const void* b){
    struct Employee* Ea = (struct Employee*)a;
    struct Employee* Eb = (struct Employee*)b;
    if(Ea->salary - Eb->salary > EPSILON) return -1;
    if(Eb->salary - Ea->salary > EPSILON) return 1;
    int str_com = strcmp(Ea->surname, Eb->surname);
    if(str_com != 0) return -str_com;
    str_com = strcmp(Ea->firstname, Eb->firstname);
    if(str_com != 0) return -str_com;
    return Eb->id - Ea->id;
}

void write_to_file(FILE* file_out, struct Employee* emp, int len){
    for (int i = 0; i < len; ++i)
    {
        fprintf(file_out, "%d:%s:%s:%lf\n", emp[i].id, emp[i].firstname, emp[i].surname, emp[i].salary);
    }
}

