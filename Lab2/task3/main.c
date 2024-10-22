#include "task3.h"

int main(){
    char file_1[] = "test1.txt";
    char file_2[] = "test2.txt";
    char substr[] = "hell\no";
    struct Sub * subs = NULL;
    int len = 0;
    if (find_substring_in_file(&subs, substr, &len, 2, file_1, file_2) != OK)
    {
        printf("invalid number of arguments\n");
        return INVALID_INPUT;
    }

    struct Sub * current = subs;
    int k = 0;
    while(current != NULL)
    {
        if(current->flag_open == 0)
        {
            printf("The file %s did not open\n", current->filename);
        }
        else
        {
            printf("File: %s, №string %d: index:%d\n", current->filename, current->line, current->index);
            k++;
        }
        current = current->next;
    }
    if(k == 0){
        printf("Not have\n");
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