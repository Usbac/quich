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
