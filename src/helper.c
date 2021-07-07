#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "helper.h"


static void prependChar(char **str, char ch)
{
    size_t len = strlen(*str) + 2;
    char *tmp = strDup(*str);

    free(*str);
    *str = malloc_(len);
    *str[0] = '\0';
    snprintf(*str, len, "%c%s", ch, tmp);

    free(tmp);
}


void *malloc_(size_t size)
{
    void *alloc_mem = malloc(size);

    if (!alloc_mem) {
        printf(ERROR_MEM_MSG);
        exit(-1);
    }

    return alloc_mem;
}


char *strDup(const char *src)
{
    char *new;
    size_t len;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src) + 1;
    new = malloc_(len);
    snprintf(new, len, "%s", src);

    return new;
}


int strncpy_(char *dest, const char *src, size_t n)
{
    snprintf(dest, n, "%s", src);

    return n;
}


double getRand(void)
{
    srand(time(NULL));
    return (double) abs(rand() * 100) / RAND_MAX;
}


double round_(double n, size_t digits)
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
    size_t len;
    size_t new_len;
    char *dot, *tmp = NULL;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    new_len = len;
    dot = strchr(str, '.');

    if (dot != NULL) {
        dot_index = dot - str;
        tmp = malloc_(len - dot_index + 1);
        strncpy_(tmp, str + dot_index, len - dot_index + 1);
    } else {
        dot_index = len;
        tmp = malloc_(1);
        tmp[0] = '\0';
    }

    for (i = dot_index - 1; i >= 0; i--) {
        if (i >= 0 && char_n > 0 && char_n % 3 == 0) {
            prependChar(&tmp, ',');
            new_len++;
        }

        prependChar(&tmp, str[i]);
        char_n++;
    }

    strncpy_(str, tmp, new_len + 1);
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


void appendChar(char **str, char ch)
{
    const size_t len = strlen(*str);
    *str = realloc(*str, len + 2);
    snprintf((*str) + len, 2, "%c", ch);
}


bool isEmpty(const char *str)
{
    return str == NULL || !strcmp(str, "");
}
