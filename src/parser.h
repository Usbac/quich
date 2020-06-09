#ifndef PARSER_H_
#define PARSER_H_
#define TOKEN_WARNING_MSG "\nWarning: Invalid token '%s'"
#define ZERO_DIVISION_WARNING_MSG "\nWarning: Division by zero/undefined."
#define TRIGONOMETRIC_WARNING_MSG "\nWarning: Invalid trigonometric value."
#define INACCURATE_RESULT_MSG "\nResult may not be correct!\n"
#define M_PI acos(-1)
/* Units of measurement for data storage (in kb) */
#define ONE_MB 1024
#define ONE_GB 1024 * 1024
#define ONE_TB 1024 * 1024 * 1024
#define ONE_PT 1024 * 1024 * 1024 * 1024

extern int precision;
extern int result_precision;
extern int degree;
extern int division_warning;

/**
 * Converts the tokens linked list to a postfix notation,
 * storing it in the operands list.
 */
void infixToPostfix(list *tokens, list *operands, list *operators);

/**
 * Returns true if the first token has a higher or equal
 * precedence than the second, false otherwise.
 * @param first the first token.
 * @param second the second token.
 */
int hasHigherEqualPrec(token_t *first, token_t *second);

/**
 * Resets the main variables like the warnings
 * and linked lists.
 */
void resetVariables(void);

/**
 * Pops one token from one list and pushes it into
 * the other.
 * @param dest the destination list
 * @param src the source list
 */
void moveToken(list **dest, list **src);

/**
 * Pushes one token into the giving list.
 * @param list the list.
 * @param node the token to push.
 */
void push(list **list, const token_t *node);

/**
 * Frees all the result stack.
 */
void freeResult(void);

/**
 * Evaluates the given postfix operation and returns its result.
 * @param postfix the list.
 * @return the result of the operation.
 */
double calc(list *postfix);

/**
 * Prints all the warnings.
 * @param list the list.
 */
void printWarnings(list *list);

/**
 * Pushes the result of a node into the given list.
 * @param list the list.
 * @param node the node.
 */
void pushResult(list *list, token_t *node);

/**
 * Pops one node from the giving list and returns its value
 * as a double.
 * @param list the list.
 */
double popNumber(list *list);

/**
 * Returns the result of the operation.
 * @param operator the operator.
 * @param x the first value.
 * @param y the second value.
 * @return the result of the operation.
 */
double getResult(const char *operator, double x, double y);

#endif /* PARSER_H_ */
