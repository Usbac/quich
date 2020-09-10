#ifndef LEXER_H_
#define LEXER_H_

#include <stdbool.h>

enum TOKEN_TYPE {
    Operand,
    Operator,
    Word,
    None
};

enum OPCODE {
    OP_Plus,
    OP_Minus,
    OP_Multi,
    OP_Div,
    OP_Equal,
    OP_Pow,
    OP_Fact,
    OP_Sqrt,
    OP_Abs,
    OP_Log,
    OP_Floor,
    OP_Ceil,
    OP_Round,
    OP_Rand,
    OP_Mb,
    OP_Gb,
    OP_Tb,
    OP_Pb,
    OP_Sin,
    OP_Cos,
    OP_Tan,
    OP_Asin,
    OP_Acos,
    OP_Atan,
    OP_Closed_parenthesis,
    OP_Open_parenthesis,
    OP_None,
};

struct token {
    char *value;
    enum OPCODE opcode;
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
 * @param opcode the opcode.
 * @return the precedence of the given operator.
 */
int getPrec(enum OPCODE opcode);

/**
 * Returns true if the given opcode represents an operator,
 * false otherwise.
 * @param opcode the opcode.
 * @return true if the given opcode represents an operator,
 * false otherwise.
 */
bool isOperator(enum OPCODE opcode);

/**
 * Returns true if the given opcode represents a function,
 * false otherwise.
 * @param opcode the opcode.
 * @return true if the given opcode represents a function,
 * false otherwise.
 */
bool isFunction(enum OPCODE opcode);

/**
 * Returns true if the given opcode represents a trigonometric function,
 * false otherwise.
 * @param opcode the opcode.
 * @return true if the given opcode represents a trigonometric function,
 * false otherwise.
 */
bool isTrigonometric(enum OPCODE opcode);

/**
 * Returns true if the given opcode represents an
 * unit of measurement for data storage (megabyte to petabyte),
 * false otherwise.
 * @param opcode the opcode.
 * @return true if the given opcode represents an
 * unit of measurement for data storage,
 * false otherwise.
 */
bool isDataUnit(enum OPCODE opcode);

/**
 * Returns true if the given token is a valid value
 * (function, operator or number), false otherwise.
 * @param node the token.
 * @return Returns true if the given node is a valid value,
 * false otherwise.
 */
bool isValid(struct token *node);

#endif /* LEXER_H_ */
