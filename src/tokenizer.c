#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tokenizer.h"
#include "helper.h"

token_t *token_head, *token_first;

char *current_token;
enum TOKEN_TYPE current_type;


void tokenize(const char *func)
{
    size_t i;

    token_head = NULL;
    token_first = NULL;
    current_token = NULL;
    current_type = None;

    current_token = malloc_(1 * sizeof(char));
    current_token[0] = '\0';

    for (i = 0; i <= strlen(func); i++) {
        processChar(func, i);
    }

    free(current_token);
}


void freeTokenize(void)
{
    token_t *node = token_first,
        *tmp;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp->val);
        free(tmp);
    }
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


void addToken(const char *token)
{
    size_t token_len;
    token_t *new = calloc(3, sizeof(token_t));
    char *token_val;

    if (token == NULL ||
        !strcmp(token, "")) {
        return;
    }

    getTokenVal(&token_val, token);

    token_len = strlen(token_val) + 1;

    new->next = NULL;
    new->val = malloc_(token_len * sizeof(char));
    strncpy_(new->val, token_val, token_len);
    free(token_val);

    if (token_head == NULL) {
        token_head = new;
        token_first = token_head;
        return;
    }

    token_head->next = new;
    token_head = new;
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

    *dest = malloc_(token_len * sizeof(char));
    strncpy_(*dest, token, token_len);
}


void processChar(const char *str, int i)
{
    if (str[i] == ' ') {
        return;
    }

    if (current_type == None) {
        current_type = getType(str[i]);
    }

    /* Add token */
    if (((int)getType(str[i]) != (int)current_type || current_type == Operator)) {
        addToken(current_token);

        free(current_token);
        current_token = malloc_(1 * sizeof(char));
        current_token[0] = '\0';
        current_type = getType(str[i]);
    }

    /* Allow signed numbers */
    if (isSigned(str, i)) {
        current_type = Operand;
        free(current_token);
        current_token = malloc_(2 * sizeof(char));
        current_token[0] = str[i];
        current_token[1] = '\0';

        return;
    }

    appendChar(&current_token, str[i]);
}


int isSigned(const char *str, int i)
{
    if (str[i] != '+' && str[i] != '-') {
        return 0;
    }

    if (i-1 < 0) {
        return 1;
    }

    return (((int)getType(str[i-1]) == Operator && str[i-1] != ')' && str[i-1] != '!') &&
        (token_head == NULL || !isNumber(token_head->val)));
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
        !strcmp(str, "!"));
}


int isTrigonometric(const char *str)
{
    return
        !strcmp(str, "sin") || !strcmp(str, "cos") || !strcmp(str, "tan") ||
        !strcmp(str, "asin") || !strcmp(str, "acos") || !strcmp(str, "atan");
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
        isNumber(str);
}
