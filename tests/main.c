#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../src/helper.h"
#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/variable.h"

size_t failed = 0;


/**
 * -1 ignore.
 * 0 failure.
 * 1 success.
 */
static char *getOpResult(const char *op)
{
    struct list *tokens, *output;
    char *result;

    initList(&tokens);
    initList(&output);

    result = getResult(op, tokens, output);

    freeList(tokens);
    freeList(output);

    return result;
}


static void assertEqual(const char *expected, char *op)
{
    char *cpy = malloc_(strlen(op) + 1);
    char *statement;

    strcpy(cpy, op);
    statement = strtok(cpy, STMT_SEPARATOR);

    while (statement != NULL) {
        char *result = getOpResult(statement);
        bool success = result == NULL || !strcmp(expected, result);

        if (result != NULL) {
            printf("%s -> %s\n", success ? "success" : "failure", op);

            if (!success) {
                printf("  Expected '%s' got '%s'.\n", expected, result);
                failed++;
            }
        }

        free(result);
        statement = strtok(NULL, STMT_SEPARATOR);
    }

    free(cpy);
}


static void setUp(void)
{
    addVariable("PI", MATH_PI);
    addVariable("E", MATH_E);
    addVariable("G", MATH_G);
    addVariable("GR", MATH_GR);
}


static void tearDown(void)
{
    freeVariables();
}


int main(int argc, char* argv[])
{
    setUp();
    assertEqual("9", "9");
    assertEqual("5", "(3+2)");
    assertEqual("4", "(3+2)-1");
    assertEqual("7", "5--2");
    assertEqual("5", "a=1;4+a");
    assertEqual("21", "a=20;a+1");
    assertEqual("10.8377655357568", "5+(cos(2)-2)^2");
    assertEqual("8.14159265358979", "5+PI");
    assertEqual("7.61803398874989", "6+GR");
    assertEqual("25", "a=12;b=a;a+b+1");
    assertEqual("0.282777605186477", "sin(1)+cos(2)+tan(3)");
    assertEqual("51", "abs(-53 + 2)");
    assertEqual("5", "floor(4.8)+ceil(0.3)");
    assertEqual("0.693147180559945", "log(2)");
    assertEqual("1.4142135623731", "sqrt(1+0.5+0.5)");
    assertEqual("nan", "sqrt(-2)");
    result_precision = 2;
    assertEqual("0.12", "0.123456");
    degree = 1;
    assertEqual("1", "sin(90)");
    tearDown();

    if (failed >= 1) {
        printf("\nFailed tests: %zu.\n", failed);
        return 1;
    }

    printf("\nAll tests have succeeded.\n");
    return 0;
}
