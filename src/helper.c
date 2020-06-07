#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"


void *malloc_(size_t size)
{
    void *alloc_mem = malloc(size);

    if (!alloc_mem) {
        printf(ERROR_MEM_MSG);
        exit(-1);
    }

    return alloc_mem;
}


int strncpy_(char *dest, const char *src, size_t n)
{
    snprintf(dest, n, "%s", src);

    return n;
}


double round_(double n, size_t digits)
{
    double decimals = pow(10, digits);
    n *= decimals;
    n = (n >= (floor(n) + 0.5f)) ?
        ceil(n) :
        floor(n);

    return n / decimals;
}


double strToDouble(char *str)
{
    size_t len;
    int factorial = 0;

    if (str == NULL) {
        return 0.0;
    }

    len = strlen(str) - 1;

    return strtod(str, NULL);
}


void addThousandsSep(char *str)
{
    int i, dot_index, char_n = 0;
    int length = strlen(str);
    int new_length = length;
    char *dot, *tmp;

    strReverse(&str);

    dot_index = ((dot = strchr(str, '.')) != NULL) ?
        (dot - str) + 1 :
        0;

    tmp = malloc_(1 * sizeof(char));
    tmp[0] = '\0';

    for (i = 0; i <= length; i++) {
        if (i > dot_index) {
            char_n++;
        }

        if (i < length && char_n > 0 && char_n % 3 == 0) {
            appendChar(&tmp, ',');
            new_length++;
        }

        appendChar(&tmp, str[i]);
    }

    strReverse(&tmp);
    strncpy_(str, tmp, new_length + 1);
    free(tmp);
}


void strReverse(char **str)
{
    char *p1 = *str;
    char tmp;
    char *p2 = *str + strlen(*str) - 1;

    while (p1 < p2) {
        tmp = *p1;
        *p1++ = *p2;
        *p2-- = tmp;
    }
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


void appendChar(char **str, const char ch)
{
    size_t length = strlen(*str) + 1;
    char *tmp = malloc_(length * sizeof(char));
    strncpy_(tmp, *str, length);

    *str = realloc(*str, length + 1 * sizeof(char));
    *str[0] = '\0';
    snprintf(*str, length + 2, "%s%c", tmp, ch);
    free(tmp);
}


int isEmpty(const char *str)
{
    return !strcmp(str, "");
}
