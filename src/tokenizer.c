#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tokenizer.h"
#include "helper.h"

char *current_token;
enum TOKEN_TYPE current_type;


void tokenize(list *list, const char *func)
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


void freeList(list *list)
{
    token_t *node;

    while ((node = list->first) != NULL) {
        list->first = list->first->next;
        free(node->val);
        free(node);
    }

    free(list);
}


void initList(list **list)
{
    (*list) = malloc_(sizeof(struct list_struct));
    (*list)->last = NULL;
    (*list)->first = NULL;
}


enum TOKEN_TYPE getType(char ch)
{
    if ((ch >= '0' && ch <= '9') || ch == '.') {
        return Operand;
    }

    if (ch == '(' || ch == ')' ||
        ch == '+' || ch == '-' ||
        ch == '/' || ch == '*' ||
        ch == '^' || ch == '!') {
        return Operator;
    }

    if ((ch>='a' && ch<='z') ||
        (ch>='A' && ch<='Z')) {
        return Word;
    }

    return None;
}


void addToken(list *list, const char *token)
{
    size_t token_len;
    token_t *new = calloc(3, sizeof(token_t));
    char *token_val;

    if (token == NULL || isEmpty(token)) {
        return;
    }

    getTokenVal(&token_val, token);

    token_len = strlen(token_val) + 1;

    new->next = NULL;
    new->val = malloc_(token_len * sizeof(char));
    strncpy_(new->val, token_val, token_len);
    free(token_val);

    /* Put zero between two adjacent parentheses */
    if (list->last != NULL && !strcmp(list->last->val, "(") &&
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


void getTokenVal(char **dest, const char *token)
{
    size_t token_len = strlen(token) + 1;

    if (!strcmp(token, "PI")) {
        *dest = malloc_(BUFFER * sizeof(char));
        snprintf(*dest, BUFFER, NUMBER_FORMAT, M_PI);
        return;
    }

    if (!strcmp(token, "E")) {
        *dest = malloc_(BUFFER * sizeof(char));
        snprintf(*dest, BUFFER, NUMBER_FORMAT, M_E);
        return;
    }

    if (!strcmp(token, "G")) {
        *dest = malloc_(BUFFER * sizeof(char));
        snprintf(*dest, BUFFER, NUMBER_FORMAT, G);
        return;
    }

    *dest = malloc_(token_len * sizeof(char));
    strncpy_(*dest, token, token_len);
}


void processChar(list *list, const char *str, int i)
{
    if (isIgnorableChar(str[i])) {
        return;
    }

    if (current_type == None) {
        current_type = getType(str[i]);
    }

    /* Add token */
    if ((int)getType(str[i]) != (int)current_type || current_type == Operator) {
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


int isIgnorableChar(char ch)
{
    return ch == ' ' || ch == ',';
}


int isSigned(list *list, const char *str, int i)
{
    if (str[i] != '+' && str[i] != '-') {
        return 0;
    }

    if (i-1 < 0) {
        return 1;
    }

    return ((int)getType(str[i-1]) == Operator && str[i-1] != ')' && str[i-1] != '!') &&
        (list->last == NULL || !isNumber(list->last->val));
}


int getPrec(const char *str)
{
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
        !strcmp(str, "^");
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
        !strcmp(str, "sin") || !strcmp(str, "cos") || !strcmp(str, "tan") ||
        !strcmp(str, "asin") || !strcmp(str, "acos") || !strcmp(str, "atan");
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
        // Signed number
        if (i == 0 && (str[i] == '-' || str[i] == '+')) {
            continue;
        }

        // Exponent number
        if (i != 0 && i+1 < len && str[i] == 'e' && (str[i+1] == '+' || str[i+1] == '-')) {
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
        isDataUnit(str);
}
