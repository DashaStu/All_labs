#include "task1.h"

enum errors reverse_str(char** result, const int len) {
    char* cop_res = (char*)malloc(sizeof(char) * len);
    if (cop_res == NULL) {
        return INVALID_MEMORY;
    }

    for (int i = 0; i < len; i++) {
        cop_res[i] = (*result)[i];
    }

    for (int i = len - 1; i >= 0; i--) {
        (*result)[len - i - 1] = cop_res[i];
    }

    (*result)[len] = '\0';
    free(cop_res);
    return OK;
}

enum errors to_2r(int number, int r, char** result) {
    if (r < 1 || r > 5) {
        return INVALID_INPUT;
    }

    int cap = 2;
    (*result) = (char*)malloc(cap * sizeof(char));
    if ((*result) == NULL) {
        return INVALID_MEMORY;
    }

    int maska = (1 << r) - 1;
    int i = 0;

    while (number > 0) {
        char c = number & maska;
        if (c < 10) {
            (*result)[i++] = c + '0';
        } else {
            (*result)[i++] = c - 10 + 'A';
        }

        number >>= r;
        if (i == cap) {
            cap *= 2;
            char* for_realloc = (char*)realloc((*result), cap * sizeof(char));
            if (for_realloc == NULL) {
                free((*result));
                return INVALID_MEMORY;
            }
            (*result) = for_realloc;
        }
    }


    return  reverse_str(result, i);
}
