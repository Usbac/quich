#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "helper.h"
#include "lexer.h"
#include "parser.h"
#include "variable.h"
#include "quich.h"

/**
 * Verbose mode or not.
 */
bool verbose = false;

/**
 * Number of flags used.
 */
int flags_quantity = 0;

/**
 * Interactive mode or not.
 */
bool interactive_mode = false;

/**
 * Using thousands separator or not.
 */
bool thousands_sep = false;

/**
 * Format to display the results.
 */
char *format = NULL;


static void printVerbose(struct list *tokens, struct list *output)
{
    struct token *node = tokens->first;

    /* Tokens */
    printf("Tokens > ");
    while (node != NULL) {
        printf(isValid(node) ? "'%s' " : "'%s'? ", node->value);
        node = node->next;
    }

    node = output->first;

    /* Postfix operation */
    printf("\nPosfix > ");
    while (node != NULL) {
        printf("%s ", node->value);
        node = node->next;
    }

    printf("\nResult > ");
}


static void printResult(char *func)
{
    struct list *tokens, *output;
    char *result;

    initList(&tokens);
    initList(&output);

    result = getResult(func, tokens, output);

    if (!isEmpty(format)) {
        snprintf(result, BUFFER, format, strToDouble(result));
    }

    if (verbose) {
        printVerbose(tokens, output);
    }

    if (thousands_sep) {
        addThousandsSep(result);
    }

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else if (verbose) {
        printf(MSG_DEFINITION);
    }

    printWarnings(output);
    freeList(tokens);
    freeList(output);
}


static void printAll(char *func)
{
    char *statements = strtok(func, STMT_SEPARATOR);

    while (statements != NULL) {
        printResult(statements);
        statements = strtok(NULL, STMT_SEPARATOR);

        if (statements != NULL && verbose) {
            printf("\n");
        }
    }
}


/**
 * Returns true if the program flow must be stopped,
 * false otherwise.
 */
static bool mapArgs(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        /* Angles in degree */
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--degree")) {
            degree = true;
            flags_quantity++;
        }

        /* Verbose mode */
        if (!strcmp(argv[i], "-vvv") || !strcmp(argv[i], "--verbose")) {
            verbose = true;
            flags_quantity++;
        }

        /* Interactive */
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--interactive")) {
            interactive_mode = true;
            flags_quantity++;
        }

        /* Version */
        if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            printf(MSG_VERSION);
            return true;
        }

        /* Help */
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf(MSG_HELP);
            return true;
        }

        /* Thousands separator */
        if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--thousands")) {
            thousands_sep = true;
            flags_quantity++;
        }

        /* The flags below work with values */
        if (i+1 >= argc) {
            return false;
        }

        /* Result format */
        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--format")) {
            format = argv[++i];
            flags_quantity += 2;
        }

        /* Precision */
        if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--precision")) {
            precision = (int)strToDouble(argv[++i]);
            flags_quantity += 2;
        }

        /* Result precision */
        if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--round")) {
            result_precision = (int)strToDouble(argv[++i]);
            flags_quantity += 2;
        }
    }

    return false;
}


static bool processLine(void)
{
    char buffer[OPERATION_BUFFER];
    char *op;
    size_t len;

    getLine(INPUT_LINE, buffer, sizeof(buffer));

    len = strlen(buffer) + 1;
    op = malloc(len);
    /* length-1 to ignore newline character at the end */
    strncpy_(op, buffer, len - 1);

    if (!strcmp(op, CLEAR_COMMAND)) {
        clearScreen();
        free(op);
        return true;
    }

    if (!strcmp(op, EXIT_COMMAND)) {
        printf(MSG_BYE);
        free(op);
        return false;
    }

    printAll(op);
    free(op);
    return true;
}


static int interactive(void)
{
    int result;
    printf(MSG_INIT);
    while ((result = processLine()));

    return result;
}


static void addPredefValues(void)
{
    addVariable("PI", MATH_PI);
    addVariable("E", MATH_E);
    addVariable("G", MATH_G);
}


int main(int argc, char* argv[])
{
    if (mapArgs(argc, argv)) {
        return 0;
    }

    addPredefValues();
    if (interactive_mode || flags_quantity >= argc - 1) {
        interactive();
    } else {
        printAll(argv[1]);
    }

    freeVariables();

    return 0;
}
