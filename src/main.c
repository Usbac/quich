#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "helper.h"
#include "lexer.h"
#include "parser.h"
#include "variable.h"
#include "main.h"

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
bool thousands_separator = false;

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
        printf(isValid(node->value) ? "'%s' " : "'%s'? ", node->value);
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

    if (thousands_separator) {
        addThousandsSep(result);
    }

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else if (verbose) {
        printf(DEFINITION_MSG);
    }

    printWarnings(output);
    freeList(tokens);
    freeList(output);
}


static void printAll(char *func)
{
    char *statement = strtok(func, STATEMENT_SEPARATOR);

    while (statement != NULL) {
        printResult(statement);
        statement = strtok(NULL, STATEMENT_SEPARATOR);

        if (statement != NULL && verbose) {
            printf("\n");
        }
    }
}


static void printHelp(void)
{
    printf(HELP_MSG);
}


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
            printf(VERSION_MSG);
            return true;
        }

        /* Help */
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printHelp();
            return true;
        }

        /* Thousands separator */
        if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--thousands")) {
            thousands_separator = true;
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
    char *operation;
    size_t len;

    getLine(INPUT_LINE, buffer, sizeof(buffer));

    len = strlen(buffer);
    operation = malloc(len + 1);
    strncpy_(operation, buffer, len);

    if (!strcmp(operation, CLEAR_COMMAND)) {
        clearScreen();
        return true;
    }

    if (!strcmp(operation, EXIT_COMMAND)) {
        printf(BYE_MSG);
        free(operation);
        return false;
    }

    printAll(operation);
    free(operation);
    return true;
}


static int interactive(void)
{
    int result;
    printf(INIT_MSG);
    while ((result = processLine()));

    return result;
}


static void addPredefValues(void)
{
    addVariable("PI", M_PI);
    addVariable("E", M_E);
    addVariable("G", G);
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
