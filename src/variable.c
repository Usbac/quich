#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "lexer.h"
#include "variable.h"

/**
 * Pointer to the first variable
 * of the variables list.
 */
static struct variable *variables_first;


static bool replaceVariable(const char *key, double val)
{
    struct variable *var = variables_first;

    while (var != NULL) {
        if (!strcmp(key, var->key)) {
            var->value = val;
            return true;
        }

        var = var->next;
    }

    return false;
}


bool isVariable(const char *str)
{
    struct variable *var = variables_first;

    if (str == NULL) {
        return false;
    }

    while (var != NULL) {
        if (!strcmp(str, var->key)) {
            return true;
        }

        var = var->next;
    }

    return false;
}


void addVariable(const char *key, double val)
{
    struct variable *var;

    if (replaceVariable(key, val)) {
        return;
    }

    var = malloc_(sizeof(struct variable));
    var->key = malloc_(BUFFER);
    strncpy_(var->key, key, strlen(key) + 1);
    var->value = val;

    var->next = variables_first;
    variables_first = var;
}


double getVariableValue(const char *key)
{
    struct variable *var = variables_first;

    while (var != NULL) {
        if (!strcmp(key, var->key)) {
            return var->value;
        }

        var = var->next;
    }

    return 0;
}


void freeVariables(void)
{
    struct variable *var;

    while ((var = variables_first) != NULL) {
        variables_first = variables_first->next;
        free(var->key);
        free(var);
    }

    free(variables_first);
}
