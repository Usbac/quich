#ifndef PARSER_H_
#define PARSER_H_
#define WARNING_TOKEN "\nWarning: Invalid token '%s'"
#define WARNING_ZERO_DIV "\nWarning: Division by zero/undefined."
#define WARNING_TRIGONOMETRIC "\nWarning: Invalid trigonometric value."
#define MSG_INACCURATE_RESULT "\nResult may not be correct!\n"
#define STMT_SEPARATOR ";"
#define NUMBER_FORMAT "%.15g"
/* Math values */
#define MATH_PI acos(-1)
#define MATH_E 2.71828182845904523536
#define MATH_G 9.80665
/* Units of measurement for data storage (in kb) */
#define ONE_MB 1024
#define ONE_GB 1024 * 1024
#define ONE_TB 1024 * 1024 * 1024
#define ONE_PT 1024 * 1024 * 1024 * 1024

extern int precision;
extern int result_precision;
extern bool degree;

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

#endif /* PARSER_H_ */
