#include "task4.h"

enum errors polynomial_n(double* res, double x, int n, ...){
    if (n<0){
        return INVALID_INPUT;
    }
    va_list temp;
    va_start(temp, n);
    *res = va_arg(temp, double);
    for(int i = n; i > 0;i--){
        *res = va_arg(temp, double) + (*res) * x;
        if(isnan(*res) || isinf(*res)) {
            va_end(temp);
            return OVER;
        }
    }
    va_end(temp);
    return OK;
}

bool is_valid_digit(const char c, const int base) {
    if (base <= 10) {
        return c >= '0' && c < '0' + base ;
    } else {
        return (c >= '0' && c <= '9') ||
               (toupper(c) >= 'A' && toupper(c) < 'A' + base - 10);
    }
}

bool is_valid_number(const char* num_str, const int base) {
    if (num_str[0] == '-') {
        return false;
    }
    for (int i = 0; num_str[i] != '\0'; i++) {
        if (!is_valid_digit(num_str[i], base)) {
            return false;
        }
    }

    return true;
}

bool is_kaprekar(long num, const int base) {
    long square = num * num;
    char square_str[MAX_N_SIZE];
    snprintf(square_str, sizeof(square_str), "%ld", square);
    int len = strlen(square_str);
    for (int i = 1; i < len; ++i) {
        char left_part[MAX_N_SIZE], right_part[MAX_N_SIZE];
        strncpy(left_part, square_str, i);
        left_part[i] = '\0';
        strcpy(right_part, square_str + i);
        long left_num = strtol(left_part, NULL, base);
        long right_num = strtol(right_part, NULL, base);
        if (left_num + right_num == num) {
            return true;
        }
    }
    return false;
}

enum errors kaprekar(char** result, int base, int count, ...) {
    if (base < 2 || base > 36 || count <= 0) {
        return INVALID_INPUT;
    }

    int cap = 128;
    (*result) = (char*)malloc(sizeof(char) * cap);
    if ((*result) == NULL) {
        return INVALID_MEMORY;
    }
    strcpy(*result, "");
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        char *num_str = va_arg(args, char*);

        if (!is_valid_number(num_str, base)) {
            //printf("Число некорректно для сс\n");
            continue;
        }
        char* endptr;
        long num = strtol(num_str, &endptr, base);
        if (*endptr != '\0') {
            continue;
        }
        if (is_kaprekar(num, base)) {
            int new_len = strlen(*result) + strlen(num_str) + 2;
            if (new_len > cap) {
                cap = new_len;
                char* temp = (char*)realloc(*result, cap);
                if (temp == NULL) {
                    free(*result);
                    va_end(args);
                    return INVALID_MEMORY;
                }
                *result = temp;
            }
            strcat(*result, num_str);
            strcat(*result, " ");
        }
    }
    va_end(args);
    return OK;
}


double turn(Point first, Point second, Point third) {
    return (second.x - first.x) * (third.y - first.y) - (second.y - first.y) * (third.x - first.x);
}

bool convex_polygon(int n, ...) {
    if (n < 3) {
        return false;
    }
    va_list temp;
    va_start(temp, n);

    Point first = va_arg(temp, Point);
    Point second = va_arg(temp, Point);
    Point third = va_arg(temp, Point);

    double first_turn = turn(first, second, third);
    int direction = (first_turn > 0) ? 1 : (first_turn < 0) ? -1 : 0;

    for (int i = 0; i < n - 3; i++) {
        first = second;
        second = third;
        third = va_arg(temp, Point);

        double current_turn = turn(first, second, third);
        int current_direction = (current_turn > 0) ? 1 : (current_turn < 0) ? -1 : 0;
        if (current_direction != 0 && current_direction != direction) {
            va_end(temp);
            return false;
        }
    }
    va_end(temp);
    return true;
}



