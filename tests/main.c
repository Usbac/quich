#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../src/helper.h"
#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/variable.h"

bool status = false;


/**
 * -1 ignore.
 * 0 failure.
 * 1 success.
 */
static int testOperation(const char *expected, const char *op)
{
    struct list *tokens, *output;
    char *result;
    int success = -1;

    initList(&tokens);
    initList(&output);

    result = getResult(op, tokens, output);
    if (result != NULL) {
        success = !strcmp(expected, result);
    }

    free(result);
    freeList(tokens);
    freeList(output);

    return success;
}


static void assertEqual(const char *expected, char *op)
{
    char *cpy = malloc_(strlen(op) + 1);
    char *statement;

    strcpy(cpy, op);
    statement = strtok(cpy, STATEMENT_SEPARATOR);

    while (statement != NULL) {
        int result = testOperation(expected, statement);
        if (result != -1) {
            printf("%s -> %s\n",
                result == 1 ? "success" : "failure",
                op);
        }

        if (result == 0) {
            status = true;
        }

        statement = strtok(NULL, STATEMENT_SEPARATOR);
    }
}


static void init(void)
{
    addVariable("PI", MATH_PI);
    addVariable("E", MATH_E);
    addVariable("G", MATH_G);
}


int main(int argc, char* argv[])
{
    init();
    assertEqual("5", "a=1;4+a");
    assertEqual("21", "a=20;a+1");
    assertEqual("10.8377655357568", "5+(cos(2)-2)^2");
    assertEqual("8.14159265358979", "5+PI");
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

    return status;
}
