#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "helper.h"
#include "lexer.h"
#include "variable.h"
#include "parser.h"

/**
 * Number of decimals used for the numbers.
 */
int precision = -1;

/**
 * Number of decimals used for the result.
 */
int result_precision = -1;

/**
 * Manage angles in degree or not.
 */
bool degree = false;

/**
 * Warning about division by zero.
 */
bool division_warning = false;

/**
 * Warning about an invalid value for
 * a trigonometric function.
 */
bool trigonometric_warning = false;

/**
 * The current operation is defining a variable or not.
 */
bool inside_def = false;


static void push(struct list **list, const struct token *node)
{
    struct token *new = malloc_(sizeof(struct token));

    if (isEmpty(node->value)) {
        return;
    }

    new->next = NULL;
    new->prev = NULL;
    new->opcode = node->opcode;
    new->value = strDup(node->value);

    if ((*list)->last == NULL) {
        (*list)->last = new;
        (*list)->first = new;
    } else {
        (*list)->last->next = new;
        new->prev = (*list)->last;
        (*list)->last = new;
    }
}


static void moveToken(struct list **dest, struct list **src)
{
    struct token *cpy, *tmp;

    if (!strcmp((*src)->last->value, "(")) {
        tmp = (*src)->last;
        (*src)->last = (*src)->last->prev;
        free(tmp->value);
        free(tmp);
    }

    cpy = malloc_(sizeof(struct token));
    cpy->prev = (*dest)->last;
    cpy->next = NULL;
    cpy->opcode = (*src)->last->opcode;
    cpy->value = strDup((*src)->last->value);

    if ((*dest)->last != NULL) {
        (*dest)->last->next = cpy;
    } else {
        (*dest)->first = cpy;
    }

    (*dest)->last = cpy;
    tmp = (*src)->last;
    (*src)->last = (*src)->last->prev;
    free(tmp->value);
    free(tmp);

    if ((*src)->last != NULL) {
        (*src)->last->next = NULL;
    } else {
        (*src)->first = NULL;
    }
}


static void migrateUntilParenthesis(struct list *output,
                                    struct list *operators)
{
    struct token *tmp;

    while (operators->last != NULL &&
        strcmp(operators->last->value, "(") != 0) {
        moveToken(&output, &operators);
    }

    if (operators->last != NULL && !strcmp(operators->last->value, "(")) {
        if (operators->first == operators->last) {
            operators->first = NULL;
        }

        tmp = operators->last;
        operators->last = operators->last->prev;
        free(tmp->value);
        free(tmp);
    }
}


static int hasHigherEqualPrec(struct token *first, struct token *second)
{
    return first != NULL && second != NULL &&
        getPrec(first->opcode) >= getPrec(second->opcode);
}


static void infixToPostfix(struct list *tokens,
                           struct list *output,
                           struct list *operators)
{
    struct token *node = tokens->first;

    division_warning = false;
    trigonometric_warning = false;

    while (node != NULL) {
        if (node->opcode == OP_Open_parenthesis) {
            push(&operators, node);
        } else if (node->opcode == OP_Closed_parenthesis) {
            migrateUntilParenthesis(output, operators);
        } else if (isFunction(node->opcode)) {
            push(&operators, node);
        } else if (isOperator(node->opcode)) {
            while (hasHigherEqualPrec(node, operators->last)) {
                moveToken(&output, &operators);
            }

            push(&operators, node);
        } else {
            push(&output, node);
        }

        node = node->next;
    }

    while (operators->last != NULL) {
        moveToken(&output, &operators);
    }
}


static double getValue(const char *str)
{
    return isVariable(str) ?
        getVariableValue(str) :
        strToDouble(str);
}


static double getOpResult(enum OPCODE op,
                          const char *a,
                          const char *b)
{
    double x, y;

    inside_def = op == OP_Equal;
    if (inside_def) {
        addVariable(a, getValue(b));
        return 0;
    }

    x = getValue(a);
    y = getValue(b);

    if (precision >= 0) {
        x = round_(x, precision);
        y = round_(y, precision);
    }

    if (op == OP_Plus) {
        return x + y;
    }

    if (op == OP_Minus) {
        return x - y;
    }

    if (op == OP_Multi) {
        return x * y;
    }

    if (op == OP_Div) {
        if (y == 0) {
            division_warning = true;
            return 0;
        }

        return x / y;
    }

    if (op == OP_Pow) {
        return pow(x, y);
    }

    if (op == OP_Fact) {
        return fact((int)y);
    }

    if (op == OP_Sqrt) {
        return sqrt(y);
    }

    if (op == OP_Abs) {
        return fabs(y);
    }

    if (op == OP_Log) {
        return log(y);
    }

    if (op == OP_Floor) {
        return floor(y);
    }

    if (op == OP_Ceil) {
        return ceil(y);
    }

    if (op == OP_Round) {
        return round(y);
    }

    if (op == OP_Rand) {
        return getRand();
    }

    if (op == OP_Mb) {
        return y * ONE_MB;
    }

    if (op == OP_Gb) {
        return y * ONE_GB;
    }

    if (op == OP_Tb) {
        return y * ONE_TB;
    }

    if (op == OP_Pb) {
        return y * ONE_PT;
    }

    if (degree && isTrigonometric(op)) {
        y = y / 180 * MATH_PI;
    }

    if (op == OP_Sin) {
        return sin(y);
    }

    if (op == OP_Cos) {
        return cos(y);
    }

    if (op == OP_Tan) {
        return tan(y);
    }

    if ((op == OP_Asin ||
        op == OP_Acos ||
        op == OP_Atan) &&
        (y < -1 || y > 1)) {
        trigonometric_warning = true;
        return 0;
    }

    if (op == OP_Asin) {
        return asin(y);
    }

    if (op == OP_Acos) {
        return acos(y);
    }

    if (op == OP_Atan) {
        return atan(y);
    }

    return 0;
}


static char *pop(struct list *list)
{
    struct token *tmp;
    char *str;

    if (list->last == NULL) {
        return 0;
    }

    str = strDup(list->last->value);
    tmp = list->last;
    list->last = list->last->prev;
    free(tmp->value);
    free(tmp);

    return str;
}


static void pushResult(struct list *list, const struct token *node)
{
    struct token *new;
    char *x = NULL, *y = NULL;
    double result;

    if (list == NULL || list->last == NULL) {
        return;
    }

    y = pop(list);

    if (!isFunction(node->opcode) &&
        !isDataUnit(node->opcode)) {
        x = pop(list);
    }

    result = getOpResult(node->opcode, x, y);
    if (precision >= 0) {
        result = round_(result, precision);
    }

    new = malloc_(sizeof(struct token));
    new->value = malloc_(BUFFER);
    snprintf(new->value, BUFFER, NUMBER_FORMAT, result);

    push(&list, new);
    free(new->value);
    free(new);
    free(y);

    if (x != NULL) {
        free(x);
    }
}


static double getPostfixResult(const struct list *postfix)
{
    struct list *result_list;
    struct token *node = postfix->first;
    double result = 0.0;

    initList(&result_list);

    while (node != NULL) {
        if (isOperator(node->opcode) ||
            isFunction(node->opcode) ||
            isDataUnit(node->opcode)) {
            pushResult(result_list, node);
        } else {
            push(&result_list, node);
        }

        node = node->next;
    }

    if (result_list != NULL && result_list->last != NULL) {
        result = getValue(result_list->last->value);
    }

    if (result_precision >= 0) {
        result = round_(result, result_precision);
    }

    freeList(result_list);

    return result;
}


char *getResult(const char *func,
                struct list *tokens,
                struct list *output)
{
    struct list *operators;
    char *result = malloc_(BUFFER);
    inside_def = false;
    initList(&operators);

    tokenize(tokens, func);
    infixToPostfix(tokens, output, operators);
    snprintf(result, BUFFER, NUMBER_FORMAT, getPostfixResult(output));
    freeList(operators);

    if (inside_def) {
        free(result);
        return NULL;
    }

    return result;
}


void printWarnings(const struct list *list)
{
    struct token *node = list->first;
    size_t warnings_quantity = 0;

    while (node != NULL) {
        if (!isValid(node)) {
            printf(WARNING_TOKEN, node->value);
            warnings_quantity++;
        }

        node = node->next;
    }

    if (division_warning) {
        printf(WARNING_ZERO_DIV);
        warnings_quantity++;
    }

    if (trigonometric_warning) {
        printf(WARNING_TRIGONOMETRIC);
        warnings_quantity++;
    }

    if (warnings_quantity > 0) {
        printf(MSG_INACCURATE_RESULT);
    }
}
