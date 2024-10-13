#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

enum errors {
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum errors str_to_int(char* str, int *result) {
    int size_str = strlen(str);
    if (size_str > 12) return INVALID_INPUT;
    for (int i = 0; i < size_str; i++) {
        if (str[i] == '-' && i == 0) continue;
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return INVALID_INPUT;
        }
    }
    sscanf(str, "%d", result);
    return OK;
}

enum errors generation(int start, int stop, int size, int** res) {
    (*res) = (int*)malloc(size * sizeof(int));
    if ((*res) == NULL) {
        return INVALID_MEMORY;
    }
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        (*res)[i] = rand() % (stop - start + 1) + start;
    }
    return OK;
}

enum errors max_min_swap(int** res, int size) {
    int max_i = 0, min_i = 0;
    for (int i = 0; i < size; i++) {
        if ((*res)[i] > (*res)[max_i]) max_i = i;
        if ((*res)[i] < (*res)[min_i]) min_i = i;
    }
    int temp = (*res)[max_i];
    (*res)[max_i] = (*res)[min_i];
    (*res)[min_i] = temp;
    return OK;
}

int find_closest(int* B, int size_B, int target) {
    int low = 0;
    int high = size_B - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (B[mid] == target) {
            return B[mid];
        }

        if (target < B[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if (high < 0) {
        return B[0];
    }
    if (low >= size_B) {
        return B[size_B - 1];
    }

    if (abs(B[low] - target) < abs(B[high] - target)) {
        return B[low];
    } else {
        return B[high];
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void sort_array(int* arr, int size) {
    qsort(arr, size, sizeof(int), compare);
}

enum errors generation_C(int** result, int** ArA, int** ArB, int s_a, int s_b) {
    (*result) = (int*)malloc(s_a * sizeof(int));
    if ((*result) == NULL) {
        return INVALID_MEMORY;
    }
    for (int i = 0; i < s_a; i++) {
        (*result)[i] = (*ArA)[i] + find_closest(*ArB, s_b, (*ArA)[i]);
        //printf("%d %d\n", (*ArA)[i], find_closest(*ArB, s_b, (*ArA)[i]));
    }
    return OK;
}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 3: {
            int a, b;
            if (str_to_int(argv[1], &a) != OK || str_to_int(argv[2], &b) != OK || a > b) {
                printf("Некорректный ввод\n");
                return INVALID_INPUT;
            }
            int size_array = 25;
            int* array = NULL;
            if (generation(a, b, size_array, &array) != OK) {
                printf("Error memory\n");
                if (array != NULL) free(array);
                return INVALID_MEMORY;
            }
            printf("Before function: ");
            for (int i = 0; i < size_array; i++) {
                printf("%d ", array[i]);
            }
            max_min_swap(&array, size_array);
            printf("\nAfter function: ");
            for (int i = 0; i < size_array; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
            if (array != NULL) free(array);
            break;
        }
        case 1: {
            int size_A, size_B, start = -1000, stop = 1000;
            size_A = 10;//rand() % (10000 - 10 + 1) + 10;
            size_B = 10;//rand() % (10000 - 10 +1) + 10;
            int* array_A = NULL;
            int* array_B = NULL;

            srand(time(NULL));
            if (generation(start, stop, size_A, &array_A) != OK || generation(start, stop, size_B, &array_B) != OK) {
                printf("Error memory\n");
                if (array_A != NULL) free(array_A);
                if (array_B != NULL) free(array_B);
                return INVALID_MEMORY;
            }
            sort_array(array_B, size_B);
            int* array_C = NULL;
            if (generation_C(&array_C, &array_A, &array_B, size_A, size_B) != OK) {
                printf("Error memory\n");
                if (array_A != NULL) free(array_A);
                if (array_B != NULL) free(array_B);
                if (array_C != NULL) free(array_C);
                return INVALID_MEMORY;
            }

            printf("Array A: ");
            for (int i = 0; i < size_A; i++) {
                printf("%d ", array_A[i]);
            }
            printf("\nArray B: ");
            for (int i = 0; i < size_B; i++) {
                printf("%d ", array_B[i]);
            }
            printf("\nArray C: ");
            for (int i = 0; i < size_A; i++) {
                printf("%d ", array_C[i]);
            }
            printf("\n");

            if (array_A != NULL) free(array_A);
            if (array_B != NULL) free(array_B);
            if (array_C != NULL) free(array_C);
            break;
        }
        default: {
            printf("Некорректный ввод\n");
            return INVALID_INPUT;
        }
    }

    return 0;
}
