#include "task3.h"

int main(){
    char file_1[] = "test1.txt";
    char file_2[] = "test2.txt";
    /*FILE* f1 = fopen(file_1, "r");
    FILE* f2 = fopen(file_2, "r");
    if(f1 == NULL || f2 == NULL){
        printf("fuck\n");
    }
    else printf("GOOD\n");*/
    char substr[] = "hello";
    struct Sub * subs = NULL;
    int len = 0;
    if (find_substring_in_file(&subs, substr, &len, 2, file_1, file_2) != OK)
    {
        printf("invalid number of arguments\n");
        return INVALID_INPUT;
    }

    struct Sub * current = subs;
    while(current != NULL)
    {
        if(current->flag_open == 0)
        {
            printf("The file %s did not open\n", current->filename);
        }
        else
        {
            printf("File: %s, № string%d: index:%d\n", current->filename, current->line, current->index);
        }
        current = current->next;
    }
    current = subs;
    while(current != NULL)
    {
        struct Sub * next = current->next;
        free(current->filename);
        free(current);
        current = next;
    }
    return 0;
}