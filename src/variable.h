#ifndef VARIABLE_H
#define VARIABLE_H

struct variable {
    char *key;
    double value;
    struct variable *next;
};


/**
 * Returns true if the given string is an existing variable,
 * false otherwise.
 * @param str the string.
 * @return Returns true if the given string is an existing variable,
 * false otherwise.
 */
bool isVariable(const char *str);

/**
 * Adds a variable.
 * @param key the variable key.
 * @param val the variable value.
 */
void addVariable(const char *key, double val);

/**
 * Returns the value of the variable with the given key.
 * @param key the variable key.
 * @return the value of the variable.
 */
double getVariableValue(const char *key);

/**
 * Frees the variable list.
 */
void freeVariables(void);

#endif /* VARIABLE_H */
