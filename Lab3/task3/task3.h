#ifndef LAB1_TASK3_H
#define LAB1_TASK3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPSILON 1e-10

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_FILE,
    INVALID_MEMORY
};

typedef struct Employee{
    int id;
    char firstname[50];
    char surname[50];
    double salary;
}Employee;

enum errors check_file(char* f1, char* f2);
enum errors check_name(char*str);
enum errors file_to_array(struct Employee** result, FILE* file_in, int* len);
void write_to_file(FILE* file_out, struct Employee* emp, int len);
int compare_a(const void* a,const void* b);
int compare_d(const void* a,const void* b);

#endif //LAB1_TASK3_H
