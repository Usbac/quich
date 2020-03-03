#ifndef PARSER_H_
#define PARSER_H_
#define BUFFER 32
#define NUMBER_FORMAT "%.15g"
#define TOKEN_WARNING_MSG "\nWarning: Invalid token '%s'"

token_t *operands_first;
token_t *operands_head;
token_t *operators_first;
token_t *operators_head;
token_t *result_head;

extern int precision;

extern int result_precision;

/**
 * Converts the tokens linked list to a postfix notation,
 * storing it in the operands list.
 */
void infixToPostfix(void);

/**
 * Pops one operator from the operators list and pushes it
 * into the operands list.
 */
void operatorToOperand(void);

/**
 * Push one token into the giving list.
 * @param head the pointer to the list head.
 * @param first the pointer to the list first element.
 * @param node the token to push.
 */
void push(token_t **head, token_t **first, const token_t *node);

/**
 * Frees all the result stack.
 */
void freeResult(void);

/**
 * Evaluates the postfix operation in the operands list
 * and pushes the result in the result stack.
 * @return the result of the postfix operation.
 */
double calc(void);

/**
 * Prints the invalid tokens.
 */
void printInvalidTokens(void);

/**
 * Frees the operands and result list.
 */
void freeLists(void);

/**
 * Pushes the result of a node into the result stack.
 * @param node the node.
 */
void pushResult(token_t *node);

/**
 * Pops one node from the giving list and returns its value
 * as a double.
 * @param head the pointer to the list head.
 */
double popNumber(token_t **head);

/**
 * Returns the result of the operation.
 * @param operator the operator.
 * @param x the first value.
 * @param y the second value.
 * @return the result of the operation.
 */
double getResult(const char *operator, double x, double y);

#endif /* PARSER_H_ */
