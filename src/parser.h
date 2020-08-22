#ifndef PARSER_H_
#define PARSER_H_
#define TOKEN_WARNING_MSG "\nWarning: Invalid token '%s'"
#define ZERO_DIVISION_WARNING_MSG "\nWarning: Division by zero/undefined."
#define TRIGONOMETRIC_WARNING_MSG "\nWarning: Invalid trigonometric value."
#define INACCURATE_RESULT_MSG "\nResult may not be correct!\n"

/* Math values */
#define M_PI acos(-1)
#define M_E 2.71828182845904523536
#define G 9.80665

/* Units of measurement for data storage (in kb) */
#define ONE_MB 1024
#define ONE_GB 1024 * 1024
#define ONE_TB 1024 * 1024 * 1024
#define ONE_PT 1024 * 1024 * 1024 * 1024

extern int precision;
extern int result_precision;
extern bool degree;
extern bool division_warning;

/**
 * Adds a variable.
 * @param key the variable key.
 * @param val the variable value.
 */
void addVariable(const char *key, const char *val);

/**
 * Returns the result of the given infix operation.
 * @param func the infix function.
 * @param tokens the tokens list.
 * @param output the output list.
 * @return the result of the given function.
 */
char *getResult(const char *func,
                struct list *tokens,
                struct list *output);

/**
 * Prints all the warnings.
 * @param list the list.
 */
void printWarnings(const struct list *list);

/**
 * Frees the variable list.
 */
void freeVariables(void);

#endif /* PARSER_H_ */
