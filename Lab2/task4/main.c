#include "task4.h"

int main(){
    printf("Task 4.1\n");
    Point p1 = (Point){0, 0};
    Point p2 = (Point){1, 0};
    Point p3 = (Point){1, 1};
    Point p4 = (Point){0, 1};
    bool res;
    res = convex_polygon(4, p1, p2, p3, p4);
    if(res)
    {
        printf("Result: yes\n");
    }
    else
    {
        printf("Result: no\n");
    }
    printf("Task 4.2\n");
    double result;
    if(polynomial_n(&result, 1, 1, 0.5) == OK){
        printf("%lf\n", result);

    }
    else if(polynomial_n(&result, 1, 1, 0.5) == INVALID_INPUT){
        printf("Invalid input\n");
    }
    else{
        printf("Overflow\n");
    }
    printf("Task 4.3\n");
    char* result_3 = NULL;
    enum errors funk = kaprekar(&result_3, 10, 4, "45", "297", "10", "-123");
    if(funk == OK){
        printf("%s\n", result_3);
        if(result_3 != NULL) free(result_3);
    }
    else if(funk == INVALID_MEMORY){
        if(result_3 != NULL) free(result_3);
        printf("Invalid memory\n");
    }
    else{
        if(result_3 != NULL) free(result_3);
        printf("Invalid input\n");
    }

    return 0;
}