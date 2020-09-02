#ifndef LEXER_H_
#define LEXER_H_

#include <stdbool.h>

#define NUMBER_FORMAT "%.15g"

enum TOKEN_TYPE {
    Operand,
    Operator,
    Word,
    None
};

struct token {
    char *value;
    struct token *prev;
    struct token *next;
};

struct list {
    struct token *first;
    struct token *last;
};


/**
 * Creates a list based on the given string
 * with infix notation.
 * @param list the list.
 * @param func the infix function.
 */
void tokenize(struct list *list, const char *func);

/**
 * Frees the given list.
 * @param list the list.
 */
void freeList(struct list *list);

/**
 * Initializes the given list.
 * @param list the list.
 */
void initList(struct list **list);

/**
 * Returns the precedence of the given operator.
 * Operators with a lower precedence are evaluated first.
 * @param str the operator.
 * @return the precedence of the given operator.
 */
int getPrec(const char *str);

/**
 * Returns true if the given string represents an operator,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents an operator,
 * false otherwise.
 */
bool isOperator(const char *str);

/**
 * Returns true if the given string represents a function,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents a function,
 * false otherwise.
 */
bool isFunction(const char *str);

/**
 * Returns true if the given string represents a trigonometric function,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents a trigonometric function,
 * false otherwise.
 */
bool isTrigonometric(const char *str);

/**
 * Returns true if the given string represents an
 * unit of measurement for data storage (megabyte to petabyte),
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents an
 * unit of measurement for data storage,
 * false otherwise.
 */
bool isDataUnit(const char *str);

/**
 * Returns true if the given string is a valid value
 * (function, operator or number), false otherwise.
 * @param str the string.
 * @return Returns true if the given value is a valid value,
 * false otherwise.
 */
bool isValid(const char *str);

#endif /* LEXER_H_ */
