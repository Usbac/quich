#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "helper.h"
#include "tokenizer.h"
#include "parser.h"

int precision = -1;
int result_precision = -1;
int degree = 0;
int division_warning = 0;
int trigonometric_warning = 0;


void infixToPostfix(list *tokens, list *operands, list *operators)
{
    token_t *node = tokens->first, *tmp;

    division_warning = 0;
    trigonometric_warning = 0;

    while (node != NULL) {
        if (!strcmp(node->val, "(")) {
            push(&operators, node);
        } else if (!strcmp(node->val, ")")) {
            while (operators->last != NULL && strcmp(operators->last->val, "(")) {
                moveToken(&operands, &operators);
            }

            if (operators->last != NULL && !strcmp(operators->last->val, "(")) {
                tmp = operators->last;
                operators->last = operators->last->prev;
                free(tmp->val);
                free(tmp);
            }
        } else if (isFunction(node->val)) {
            push(&operators, node);
        } else if (isOperator(node->val)) {
            while (hasHigherEqualPrec(node, operators->last)) {
                moveToken(&operands, &operators);
            }

            push(&operators, node);
        } else {
            push(&operands, node);
        }

        node = node->next;
    }

    while (operators->last != NULL) {
        moveToken(&operands, &operators);
    }
}


int hasHigherEqualPrec(token_t *first, token_t *second)
{
    return first != NULL && second != NULL && 
        getPrec(first->val) >= getPrec(second->val);
}


void moveToken(list **dest, list **src)
{
    size_t value_len = strlen((*src)->last->val) + 1;
    token_t *cpy, *tmp;

    if (!strcmp((*src)->last->val, "(")) {
        tmp = (*src)->last;
        (*src)->last = (*src)->last->prev;
        free(tmp->val);
        free(tmp);
    }

    cpy = calloc(3, sizeof(token_t));
    cpy->prev = (*dest)->last;
    cpy->next = NULL;
    cpy->val = malloc_(value_len * sizeof(char));
    strncpy_(cpy->val, (*src)->last->val, value_len);

    if ((*dest)->last != NULL) {
        (*dest)->last->next = cpy;
    } else {
        (*dest)->first = cpy;
    }

    (*dest)->last = cpy;
    tmp = (*src)->last;
    (*src)->last = (*src)->last->prev;
    free(tmp->val);
    free(tmp);

    if ((*src)->last != NULL) {
        (*src)->last->next = NULL;
    } else {
        (*src)->first = NULL;
    }
}


void push(list **list, const token_t *node)
{
    size_t value_len = strlen(node->val) + 1;
    token_t *new = calloc(3, sizeof(token_t));

    if (node == NULL || isEmpty(node->val)) {
        return;
    }

    new->next = NULL;
    new->prev = NULL;
    new->val = malloc_(value_len);
    strncpy_(new->val, node->val, value_len);

    if ((*list)->last == NULL) {
        (*list)->last = new;
        (*list)->first = new;
    } else {
        (*list)->last->next = new;
        new->prev = (*list)->last;
        (*list)->last = new;
    }
}


double calc(list *postfix)
{
    list *result_list;
    token_t *node = postfix->first;
    double result = 0.0;

    initList(&result_list);
    
    while (node != NULL) {
        if (isOperator(node->val) ||
            isFunction(node->val) ||
            isDataUnit(node->val)) {
            pushResult(result_list, node);
        } else {
            push(&result_list, node);
        }

        node = node->next;

    }

    if (result_list != NULL && result_list->last != NULL) {
        result = strToDouble(result_list->last->val);
    }

    if (result_precision >= 0) {
        result = round_(result, result_precision);
    }

    freeList(result_list);

    return result;
}


void printWarnings(list *list)
{
    token_t *node = list->first;
    size_t warnings_quantity = 0;

    while (node != NULL) {
        if (!isValid(node->val) &&
            strcmp(node->val, "(") &&
            strcmp(node->val, ")")) {
            printf(TOKEN_WARNING_MSG, node->val);
            warnings_quantity++;
        }

        node = node->next;
    }

    if (division_warning) {
        printf(ZERO_DIVISION_WARNING_MSG);
        warnings_quantity++;
    }

    if (trigonometric_warning) {
        printf(TRIGONOMETRIC_WARNING_MSG);
        warnings_quantity++;
    }

    if (warnings_quantity > 0) {
        printf(INACCURATE_RESULT_MSG);
    }
}


void pushResult(list *list, token_t *node)
{
    double result, x = 0, y = 0;

    if (list == NULL || list->last == NULL) {
        return;
    }

    y = popNumber(list);

    if (!isFunction(node->val) &&
        !isDataUnit(node->val)) {
        x = popNumber(list);
    }

    if (precision >= 0) {
        x = round_(x, precision);
        y = round_(y, precision);
    }

    result = getResult(node->val, x, y);

    if (precision >= 0) {
        result = round_(result, precision);
    }

    free(node->val);
    node->val = malloc_(BUFFER * sizeof(char));
    snprintf(node->val, BUFFER, NUMBER_FORMAT, result);

    push(&list, node);
}


double popNumber(list *list)
{
    token_t *tmp;
    size_t len;
    char *str;
    double result;

    if (list->last == NULL) {
        return 0;
    }

    len = strlen(list->last->val) + 1;

    str = malloc_(len * sizeof(char));
    strncpy_(str, list->last->val, len);
    tmp = list->last;
    list->last = list->last->prev;
    free(tmp->val);
    free(tmp);

    result = strToDouble(str);
    free(str);
    return result;
}


double getResult(const char *operator, double x, double y)
{
    if (!strcmp(operator, "+")) {
        return x + y;
    }

    if (!strcmp(operator, "-")) {
        return x - y;
    }

    if (!strcmp(operator, "*")) {
        return x * y;
    }

    if (!strcmp(operator, "/")) {
        if (y == 0) {
            division_warning = 1;
            return 0;
        }

        return x / y;
    }

    if (!strcmp(operator, "^")) {
        return pow(x, y);
    }

    if (!strcmp(operator, "!")) {
        return fact((int)y);
    }

    if (!strcmp(operator, "sqrt")) {
        return sqrt(y);
    }

    if (!strcmp(operator, "abs")) {
        return fabs(y);
    }

    if (!strcmp(operator, "log")) {
        return log(y);
    }

    if (!strcmp(operator, "floor")) {
        return floor(y);
    }

    if (!strcmp(operator, "ceil")) {
        return ceil(y);
    }

    if (!strcmp(operator, "round")) {
        return round(y);
    }

    if (!strcmp(operator, "rand")) {
        srand(time(NULL));
        return (double) abs(rand() * 100) / RAND_MAX;
    }

    if (!strcmp(operator, "mb")) {
        return y * ONE_MB;
    }

    if (!strcmp(operator, "gb")) {
        return y * ONE_GB;
    }

    if (!strcmp(operator, "tb")) {
        return y * ONE_TB;
    }

    if (!strcmp(operator, "pb")) {
        return y * ONE_PT;
    }

    if (degree && isTrigonometric(operator)) {
        y = y / 180 * M_PI;
    }

    if (!strcmp(operator, "sin")) {
        return sin(y);
    }

    if (!strcmp(operator, "cos")) {
        return cos(y);
    }

    if (!strcmp(operator, "tan")) {
        return tan(y);
    }

    if ((!strcmp(operator, "asin") ||
        !strcmp(operator, "acos") ||
        !strcmp(operator, "atan")) &&
        (y < -1 || y > 1)) {
        trigonometric_warning = 1;
        return 0;
    }

    if (!strcmp(operator, "asin")) {
        return asin(y);
    }

    if (!strcmp(operator, "acos")) {
        return acos(y);
    }

    if (!strcmp(operator, "atan")) {
        return atan(y);
    }

    return 0;
}
