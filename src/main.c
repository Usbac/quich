#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "tokenizer.h"
#include "parser.h"
#include "main.h"

int verbose = 0;
int flags_quantity = 0;
int interactive_mode = 0;
int thousands_separator = 0;
char *format = NULL;
list *tokens, *operands, *operators;


void printResult(char *func)
{
    char *result = malloc_(BUFFER * sizeof(char));
    result[0] = '\0';
    int defined_format = format != NULL && !isEmpty(format);

    initList(&tokens);
    initList(&operands);
    initList(&operators);

    tokenize(tokens, func);
    infixToPostfix(tokens, operands, operators);

    if (verbose) {
        printVerbose();
    }

    snprintf(result, BUFFER, defined_format ? format : NUMBER_FORMAT, calc(operands));

    if (thousands_separator) {
        addThousandsSep(result);
    }

    printf("%s\n", result);
    printWarnings(operands);
    freeList(tokens);
    freeList(operands);
    freeList(operators);
    free(result);
}


void printVerbose(void)
{
    token_t *node = tokens->first;
    int is_valid = 0;

    /* Tokens */
    printf("Tokens > ");
    while (node != NULL) {
        is_valid = isValid(node->val) ||
            !strcmp(node->val, "(") ||
            !strcmp(node->val, ")");

        printf(is_valid ? "'%s' " : "'%s'? ", node->val);
        node = node->next;
    }

    node = operands->first;

    /* Postfix operation */
    printf("\nPosfix > ");
    while (node != NULL) {
        printf("%s ", node->val);
        node = node->next;
    }

    printf("\nResult > ");
}


int mapArgs(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        /* Angles in degree */
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--degree")) {
            degree = 1;
            flags_quantity++;
        }

        /* Verbose mode */
        if (!strcmp(argv[i], "-vvv") || !strcmp(argv[i], "--verbose")) {
            verbose = 1;
            flags_quantity++;
        }

        /* Interactive */
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--interactive")) {
            interactive_mode = 1;
            flags_quantity++;
        }

        /* Version */
        if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            printf(VERSION_MSG);
            return 1;
        }

        /* Help */
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printHelp();
            return 1;
        }

        /* Thousands separator */
        if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--thousands")) {
            thousands_separator = 1;
            flags_quantity++;
        }

        //The flags below work with values
        if (i+1 >= argc) {
            return 0;
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

    return 0;
}


void printHelp(void)
{
    printf(HELP_MSG);
}


int interactive(void)
{
    int result;
    printf(INIT_MSG);
    while (result = processLine());

    return result;
}


int processLine(void)
{
    char buffer[OPERATION_BUFFER];
    char *operation;
    size_t len;

    getLine(INPUT_LINE, buffer, sizeof(buffer));

    len = strlen(buffer);
    operation = malloc(len + 1 * sizeof(char));
    memset(operation, 0, len + 1);
    strncpy_(operation, buffer, len);

    if (!strcmp(operation, EXIT_COMMAND)) {
        printf(BYE_MSG);
        free(operation);
        return 0;
    }

    printResult(operation);
    free(operation);
    return 1;
}


int main(int argc, char* argv[])
{
    if (mapArgs(argc, argv)) {
        return 0;
    }

    if (interactive_mode || flags_quantity >= argc - 1) {
        return interactive();
    }

    printResult(argv[1]);
    return 0;
}
