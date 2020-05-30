#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"
#include "tokenizer.h"
#include "parser.h"

token_t *operands_first, *operands_head;
token_t *operators_first, *operators_head;
token_t *result_head;

int precision = -1;
int result_precision = -1;
int degree = 0;
int division_warning = 0;
int trigonometric_warning = 0;


void infixToPostfix(void)
{
    token_t *node = token_first, *tmp;
    operands_first = NULL;
    operands_head = NULL;
    operators_head = NULL;
    operators_first = NULL;
    result_head = NULL;
    division_warning = 0;
    trigonometric_warning = 0;

    while (node != NULL) {
        if (!strcmp(node->val, "(")) {
            push(&operators_head, &operators_first, node);
        } else if (!strcmp(node->val, ")")) {
            while (operators_head != NULL && strcmp(operators_head->val, "(")) {
                operatorToOperand();
            }

            if (operators_head != NULL && !strcmp(operators_head->val, "(")) {
                tmp = operators_head;
                operators_head = operators_head->prev;
                free(tmp->val);
                free(tmp);
            }
        } else if (isFunction(node->val)) {
            push(&operators_head, &operators_first, node);
        } else if (isOperator(node->val)) {
            while (operators_head != NULL && getPrec(node->val) >= getPrec(operators_head->val)) {
                operatorToOperand();
            }

            push(&operators_head, &operators_first, node);
        } else {
            push(&operands_head, &operands_first, node);
        }

        node = node->next;
    }

    while (operators_head != NULL) {
        operatorToOperand();
    }
}


void operatorToOperand(void)
{
    size_t value_len = strlen(operators_head->val) + 1;
    token_t *cpy, *tmp;

    if (!strcmp(operators_head->val, "(")) {
        tmp = operators_head;
        operators_head = operators_head->prev;
        free(tmp->val);
        free(tmp);
    }

    cpy = calloc(3, sizeof(token_t));
    cpy->prev = operands_head;
    cpy->next = NULL;
    cpy->val = malloc_(value_len * sizeof(char));
    strncpy_(cpy->val, operators_head->val, value_len);

    if (operands_head != NULL) {
        operands_head->next = cpy;
    } else {
        operands_first = cpy;
    }

    operands_head = cpy;
    tmp = operators_head;
    operators_head = operators_head->prev;
    free(tmp->val);
    free(tmp);

    if (operators_head != NULL) {
        operators_head->next = NULL;
    } else {
        operators_first = NULL;
    }
}


void push(token_t **head, token_t **first, const token_t *node)
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

    if ((*head) == NULL) {
        (*head) = new;
        if (first != NULL) {
            (*first) = new;
        }
    } else {
        (*head)->next = new;
        new->prev = (*head);
        (*head) = new;
    }
}


double calc(void)
{
    token_t *node = operands_first;
    double result = 0.0;

    while (node != NULL) {
        if (isOperator(node->val) ||
            isFunction(node->val)) {
            pushResult(node);
        } else {
            push(&result_head, NULL, node);
        }

        node = node->next;
    }

    if (result_head != NULL) {
        result = strToDouble(result_head->val);
    }

    if (result_precision >= 0) {
        result = round_(result, result_precision);
    }

    return result;
}


void printWarnings(void)
{
    token_t *node = operands_first;
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


void freeLists(void)
{
    token_t *node, *tmp;

    /* free operands list */
    node = operands_first;
    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp->val);
        free(tmp);
    }

    /* free result */
    node = result_head;
    while (node != NULL) {
        tmp = node;
        node = node->prev;
        free(tmp->val);
        free(tmp);
    }
}


void pushResult(token_t *node)
{
    double result, x = 0, y = 0;
    size_t len;

    if (result_head == NULL) {
        return;
    }

    y = popNumber(&result_head);

    if (!isFunction(node->val)) {
        x = popNumber(&result_head);
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

    push(&result_head, NULL, node);
}


double popNumber(token_t **head)
{
    token_t *tmp;
    size_t len;
    char *str;
    double result;

    if ((*head) == NULL) {
        return 0;
    }

    len = strlen((*head)->val) + 1;

    str = malloc_(len * sizeof(char));
    strncpy_(str, (*head)->val, len);
    tmp = (*head);
    (*head) = (*head)->prev;
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
