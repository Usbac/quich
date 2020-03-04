#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "helper.h"
#include "tokenizer.h"
#include "parser.h"

int verbose = 0;


void print(char *func)
{
    tokenize(func);
    infixToPostfix();

	if (verbose) {
		printVerbose();
	}

    freeTokenize();
    printf(NUMBER_FORMAT"\n", calc());
    printInvalidTokens();
    freeLists();
}


void printVerbose(void)
{
	token_t *node = token_first;

	printf("Tokens > ");
	while (node != NULL) {
		printf("'%s' ", node->val);
		node = node->next;
	}

	node = operands_first;

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
		/* Verbose mode */
		if (!strcmp(argv[i], "-vvv") || !strcmp(argv[i], "--verbose")) {
            verbose = 1;
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

		if (i+1 > argc) {
			return 0;
		}

        /* Precision */
		if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--precision")) {
            precision = (int)strToDouble(argv[++i]);
		}

        /* Result precision */
		if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--round")) {
            result_precision = (int)strToDouble(argv[++i]);
		}

	}

	return 0;
}


void printHelp(void)
{
    printf(HELP_MSG);
}


int read(void)
{
    char buffer[OPEATION_BUFFER];
    char *operation;
    size_t len;

    printf(INIT_MSG);

    while (1) {
        getLine("> ", buffer, sizeof(buffer));

        len = strlen(buffer);
        operation = malloc(len + 1 * sizeof(char));
        memset(operation, 0, len + 1);
        strncpy_(operation, buffer, len);

        if (!strcmp(operation, EXIT_COMMAND)) {
            printf(BYE_MSG);
            free(operation);
            return 0;
        }

        print(operation);
        free(operation);
    }

    return 1;
}


int main(int argc, char* argv[])
{
    if (argc == 1) {
        return read();
    }

    if (mapArgs(argc, argv)) {
        return 0;
    }

    print(argv[1]);
    return 0;
}
