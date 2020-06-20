#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"


void *malloc_(const size_t size)
{
    void *alloc_mem = malloc(size);

    if (!alloc_mem) {
        printf(ERROR_MEM_MSG);
        exit(-1);
    }

    return alloc_mem;
}


int strncpy_(char *dest, const char *src, const size_t n)
{
    snprintf(dest, n, "%s", src);

    return n;
}


double round_(double n, const size_t digits)
{
    double decimals = pow(10, digits);
    n *= decimals;
    n = (n >= floor(n) + 0.5f) ?
        ceil(n) :
        floor(n);

    return n / decimals;
}


double strToDouble(const char *str)
{
    if (str == NULL) {
        return 0.0;
    }

    return strtod(str, NULL);
}


void addThousandsSep(char *str)
{
    int i, dot_index, char_n = 0;
    int length;
    int new_length;
    char *dot, *tmp = NULL;

    if (str == NULL) {
        return;
    }

    length = strlen(str);
    new_length = length;
    dot = strchr(str, '.');

    if (dot != NULL) {
        dot_index = dot - str;
        tmp = malloc_(length - dot_index + 1 * sizeof(char));
        strncpy_(tmp, str + dot_index, length - dot_index + 1);
    } else {
        dot_index = length;
        tmp = malloc_(1 * sizeof(char));
        tmp[0] = '\0';
    }

    for (i = dot_index - 1; i >= 0; i--) {
        if (i >= 0 && char_n > 0 && char_n % 3 == 0) {
            addChar(&tmp, ',', 1);
            new_length++;
        }

        addChar(&tmp, str[i], 1);
        char_n++;
    }

    strncpy_(str, tmp, new_length + 1);
    free(tmp);
}


long int fact(long int n)
{
    long int next;

    if (n == 1 || n == 0) {
        return 1;
    }

    next = (n < 0) ? n + 1 : n - 1;

    return n * fact(next);
}


void getLine(const char *str, char *buffer, size_t size)
{
    size_t len;

    if (str != NULL) {
        printf("%s", str);
    }

    if (fgets(buffer, size, stdin) == NULL) {
        printf("\r");
        exit(0);
    }

    len = strlen(buffer);
    if (len <= 0 || buffer[len - 1] == '\n') {
        return;
    }

    while (getchar() != '\n');
}


void addChar(char **str, const char ch, int begin)
{
    size_t length = strlen(*str) + 1;
    char *tmp = malloc_(length + 1 * sizeof(char));
    strncpy_(tmp, *str, length);

    free(*str);
    *str = malloc_(length + 1 * sizeof(char));
    *str[0] = '\0';

    if (begin) {
        snprintf(*str, length + 2, "%c%s", ch, tmp);
    } else {
        snprintf(*str, length + 2, "%s%c", tmp, ch);
    }

    free(tmp);
}


int isEmpty(const char *str)
{
    return str == NULL || !strcmp(str, "");
}


void clearScreen(void)
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
