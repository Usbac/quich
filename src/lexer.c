#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "variable.h"
#include "lexer.h"

/**
 * Current token being used.
 */
char *current_token;

/**
 * Type of the current token being used.
 */
enum TOKEN_TYPE current_type;


static enum TOKEN_TYPE getType(const char ch)
{
    if ((ch >= '0' && ch <= '9') || ch == '.') {
        return T_Operand;
    }

    if (ch == '(' || ch == ')' ||
        ch == '+' || ch == '-' ||
        ch == '/' || ch == '*' ||
        ch == '^' || ch == '!' ||
        ch == '=') {
        return T_Operator;
    }

    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z')) {
        return T_Word;
    }

    return T_None;
}


static bool isIgnorableC(const char ch)
{
    return ch == ' ' || ch == ',';
}


static bool isNumber(const char *str)
{
    size_t len = strlen(str);
    size_t i;

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
            return false;
        }
    }

    return true;
}


static bool isSigned(struct list *list, const char *str, const int i)
{
    if (str[i] != '+' && str[i] != '-') {
        return false;
    }

    if (i-1 < 0) {
        return true;
    }

    return
            (getType(str[i-1]) == T_Operator && str[i - 1] != ')' && str[i - 1] != '!') &&
            (list->last == NULL || !isNumber(list->last->value));
}


static void prependList(struct list *list, struct token *node)
{
    if (list->last == NULL) {
        list->last = node;
        list->first = list->last;
        return;
    }

    list->last->next = node;
    list->last = node;
}


static enum OPCODE getOpcode(const char *str)
{
    if (!strcmp(str, "+")) {
        return OP_Plus;
    } else if (!strcmp(str, "-")) {
        return OP_Minus;
    } else if (!strcmp(str, "*")) {
        return OP_Multi;
    } else if (!strcmp(str, "/")) {
        return OP_Div;
    } else if (!strcmp(str, "=")) {
        return OP_Equal;
    } else if (!strcmp(str, "^")) {
        return OP_Pow;
    } else if (!strcmp(str, "!")) {
        return OP_Fact;
    } else if (!strcmp(str, "sqrt")) {
        return OP_Sqrt;
    } else if (!strcmp(str, "abs")) {
        return OP_Abs;
    } else if (!strcmp(str, "log")) {
        return OP_Log;
    } else if (!strcmp(str, "floor")) {
        return OP_Floor;
    } else if (!strcmp(str, "ceil")) {
        return OP_Ceil;
    } else if (!strcmp(str, "round")) {
        return OP_Round;
    } else if (!strcmp(str, "rand")) {
        return OP_Rand;
    } else if (!strcmp(str, "mb")) {
        return OP_Mb;
    } else if (!strcmp(str, "gb")) {
        return OP_Gb;
    } else if (!strcmp(str, "tb")) {
        return OP_Tb;
    } else if (!strcmp(str, "pb")) {
        return OP_Pb;
    } else if (!strcmp(str, "sin")) {
        return OP_Sin;
    } else if (!strcmp(str, "cos")) {
        return OP_Cos;
    } else if (!strcmp(str, "tan")) {
        return OP_Tan;
    } else if (!strcmp(str, "asin")) {
        return OP_Asin;
    } else if (!strcmp(str, "acos")) {
        return OP_Acos;
    } else if (!strcmp(str, "atan")) {
        return OP_Atan;
    } else if (!strcmp(str, "(")) {
        return OP_Open_parenthesis;
    } else if (!strcmp(str, ")")) {
        return OP_Closed_parenthesis;
    }

    return OP_None;
}


static void addToken(struct list *list, const char *token)
{
    size_t len;
    struct token *new;

    if (isEmpty(token)) {
        return;
    }

    len = strlen(token) + 1;

    new = calloc(3, sizeof(struct token));
    new->opcode = getOpcode(token);
    new->next = NULL;
    new->value = malloc_(len);
    strncpy_(new->value, token, len);

    /* Set zero as argument if no argument is provided */
    if (list->last != NULL && !strcmp(list->last->value, "(") &&
        !strcmp(token, ")")) {
        addToken(list, "0");
    }

    prependList(list, new);
}


static void processChar(struct list *list,
                        const char *str,
                        const int i)
{
    if (isIgnorableC(str[i])) {
        return;
    }

    if (current_type == T_None) {
        current_type = getType(str[i]);
    }

    /* Add token */
    if (getType(str[i]) != current_type ||
        current_type == T_Operator) {
        addToken(list, current_token);

        free(current_token);
        current_token = malloc_(1);
        current_token[0] = '\0';
        current_type = getType(str[i]);
    }

    /* Allow signed numbers */
    if (isSigned(list, str, i)) {
        current_type = T_Operand;
        free(current_token);
        current_token = malloc_(2);
        current_token[0] = str[i];
        current_token[1] = '\0';

        return;
    }

    addChar(&current_token, str[i], 0);
}


void tokenize(struct list *list, const char *func)
{
    size_t i;

    current_type = T_None;
    current_token = malloc_(1);
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


int getPrec(enum OPCODE opcode)
{
    if (opcode == OP_Equal) {
        return 5;
    }

    if (opcode == OP_Open_parenthesis ||
        opcode == OP_Closed_parenthesis) {
        return 4;
    }

    if (opcode == OP_Plus ||
        opcode == OP_Minus) {
        return 3;
    }

    if (opcode == OP_Multi ||
        opcode == OP_Div) {
        return 2;
    }

    if (opcode == OP_Pow) {
        return 1;
    }

    return 0;
}


bool isOperator(enum OPCODE opcode)
{
    return
        opcode == OP_Plus || opcode == OP_Minus ||
        opcode == OP_Multi || opcode == OP_Div ||
        opcode == OP_Pow || opcode == OP_Equal;
}


bool isFunction(enum OPCODE opcode)
{
    return isTrigonometric(opcode) ||
        opcode == OP_Sqrt || opcode == OP_Log ||
        opcode == OP_Floor || opcode == OP_Ceil ||
        opcode == OP_Round || opcode == OP_Abs ||
        opcode == OP_Rand || opcode == OP_Fact;
}


bool isTrigonometric(enum OPCODE opcode)
{
    return
        opcode == OP_Sin || opcode == OP_Cos ||
        opcode == OP_Tan || opcode == OP_Asin ||
        opcode == OP_Acos || opcode == OP_Atan;
}


bool isDataUnit(enum OPCODE opcode)
{
    return
        opcode == OP_Mb || opcode == OP_Gb ||
        opcode == OP_Tb || opcode == OP_Pb;
}


bool isValid(struct token *node)
{
    return isOperator(node->opcode) ||
        isFunction(node->opcode) ||
        isDataUnit(node->opcode) ||
        node->opcode == OP_Open_parenthesis ||
        node->opcode == OP_Closed_parenthesis ||
        isVariable(node->value) ||
        isNumber(node->value);
}
