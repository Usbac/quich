#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "tokenizer.h"

/**
 * Current token being used
 */
char *current_token;

/**
 * Type of the current token being used
 */
enum TOKEN_TYPE current_type;

/**
 * Pointer to the variables list
 */
struct variable *variables_first;


static enum TOKEN_TYPE getType(const char ch)
{
    if ((ch >= '0' && ch <= '9') || ch == '.') {
        return Operand;
    }

    if (ch == '(' || ch == ')' ||
        ch == '+' || ch == '-' ||
        ch == '/' || ch == '*' ||
        ch == '^' || ch == '!' ||
        ch == '=') {
        return Operator;
    }

    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z')) {
        return Word;
    }

    return None;
}


static int isIgnorableChar(const char ch)
{
    return ch == ' ' || ch == ',';
}


static int isSigned(struct list *list, const char *str, const int i)
{
    if (str[i] != '+' && str[i] != '-') {
        return 0;
    }

    if (i-1 < 0) {
        return 1;
    }

    return
        ((int)getType(str[i-1]) == Operator && str[i-1] != ')' && str[i-1] != '!') &&
        (list->last == NULL || !isNumber(list->last->value));
}


static void getTokenVal(char **dest, const char *token)
{
    size_t token_len = strlen(token) + 1;

    *dest = malloc_(token_len * sizeof(char));
    strncpy_(*dest, token, token_len);
}


static void addToken(struct list *list, const char *token)
{
    size_t token_len;
    struct token *new = calloc(3, sizeof(struct token));
    char *token_val;

    if (isEmpty(token)) {
        return;
    }

    getTokenVal(&token_val, token);

    token_len = strlen(token_val) + 1;

    new->next = NULL;
    new->value = malloc_(token_len * sizeof(char));
    strncpy_(new->value, token_val, token_len);
    free(token_val);

    /* Put zero between two adjacent parentheses */
    if (list->last != NULL && !strcmp(list->last->value, "(") &&
        !strcmp(token, ")")) {
        addToken(list, "0");
    }

    if (list->last == NULL) {
        list->last = new;
        list->first = list->last;
        return;
    }

    list->last->next = new;
    list->last = new;
}


static void processChar(struct list *list,
                        const char *str,
                        const int i)
{
    if (isIgnorableChar(str[i])) {
        return;
    }

    if (current_type == None) {
        current_type = getType(str[i]);
    }

    /* Add token */
    if (getType(str[i]) != current_type ||
        current_type == Operator) {
        addToken(list, current_token);

        free(current_token);
        current_token = malloc_(1 * sizeof(char));
        current_token[0] = '\0';
        current_type = getType(str[i]);
    }

    /* Allow signed numbers */
    if (isSigned(list, str, i)) {
        current_type = Operand;
        free(current_token);
        current_token = malloc_(2 * sizeof(char));
        current_token[0] = str[i];
        current_token[1] = '\0';

        return;
    }

    addChar(&current_token, str[i], 0);
}


void tokenize(struct list *list, const char *func)
{
    size_t i;

    current_type = None;
    current_token = malloc_(1 * sizeof(char));
    current_token[0] = '\0';

    for (i = 0; i <= strlen(func); i++) {
        processChar(list, func, i);
    }

    free(current_token);
}


void freeList(struct list *list)
{
    struct token *node;

    while ((node = list->first) != NULL) {
        list->first = list->first->next;
        free(node->value);
        free(node);
    }

    free(list);
}


void initList(struct list **list)
{
    (*list) = malloc_(sizeof(struct list));
    (*list)->last = NULL;
    (*list)->first = NULL;
}


int getPrec(const char *str)
{
    if (!strcmp(str, "=")) {
        return 5;
    }

    if (!strcmp(str, "(") ||
        !strcmp(str, ")")) {
        return 4;
    }

    if (!strcmp(str, "+") ||
        !strcmp(str, "-")) {
        return 3;
    }

    if (!strcmp(str, "*") ||
        !strcmp(str, "/")) {
        return 2;
    }

    if (!strcmp(str, "^")) {
        return 1;
    }

    return 0;
}


int isOperator(const char *str)
{
    return !strcmp(str, "+") || !strcmp(str, "-") ||
        !strcmp(str, "*") || !strcmp(str, "/") ||
        !strcmp(str, "^") || !strcmp(str, "=");
}


int isFunction(const char *str)
{
    return isTrigonometric(str) ||
        (!strcmp(str, "sqrt") || !strcmp(str, "log") ||
        !strcmp(str, "floor") || !strcmp(str, "ceil") ||
        !strcmp(str, "round") || !strcmp(str, "abs") ||
        !strcmp(str, "rand") || !strcmp(str, "!"));
}


int isTrigonometric(const char *str)
{
    return
        !strcmp(str, "sin") || !strcmp(str, "cos") ||
        !strcmp(str, "tan") || !strcmp(str, "asin") ||
        !strcmp(str, "acos") || !strcmp(str, "atan");
}


int isDataUnit(const char *str)
{
    return
        !strcmp(str, "mb") || !strcmp(str, "gb") ||
        !strcmp(str, "tb") || !strcmp(str, "pb");
}


int isNumber(const char *str)
{
    size_t len = strlen(str);
    size_t i = 0;

    for (i = 0; i < len; i++) {
        /* Signed number */
        if (i == 0 && (str[i] == '-' || str[i] == '+')) {
            continue;
        }

        /* Exponent number */
        if (i != 0 && i+1 < len && str[i] == 'e' &&
            (str[i+1] == '+' || str[i+1] == '-')) {
            i++;
            continue;
        }

        if (str[i] != '.' && (str[i] < '0' || str[i] > '9')) {
            return 0;
        }
    }

    return 1;
}


int isValid(const char *str)
{
    return isOperator(str) ||
        isFunction(str) ||
        isNumber(str) ||
        isDataUnit(str) ||
        isVariable(str);
}


int isVariable(const char *str)
{
    if (variables_first == NULL || str == NULL) {
        return 0;
    }

    struct variable *node = variables_first;

    while (node != NULL) {
        if (!strcmp(str, node->key)) {
            return 1;
        }

        node = node->next;
    }

    return 0;
}
