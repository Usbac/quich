#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#define BUFFER 32
#define NUMBER_FORMAT "%.15g"
#define M_PI acos(-1)
#define M_E 2.71828182845904523536

enum TOKEN_TYPE {
    Operand,
    Operator,
    Word,
    None
};

typedef struct token_struct {
    char *val;
    struct token_struct *prev;
    struct token_struct *next;
} token_t;

extern token_t *token_head;
extern token_t *token_first;

char *current_token;
enum TOKEN_TYPE current_type;

/**
 * Creates the token list based on the given string
 * with infix notation.
 * @param func the infix function.
 */
void tokenize(const char *func);

/**
 * Frees the token list.
 */
void freeTokenize(void);

/**
 * Returns the type of the given char.
 * @param ch the char.
 * @return
 */
enum TOKEN_TYPE getType(char ch);

/**
 * Adds a token to the token list.
 * @param token the token string.
 */
void addToken(const char *token);

/**
 * Stores the token value into the given variable.
 * @param dest the pointer to the variable where the token
 * value will be stored.
 * @param token the token string.
 */
void getTokenVal(char **dest, const char *token);

/**
 * Process the char in the given index of the string.
 * @param str the string.
 * @param i the index.
 */
void processChar(const char *str, int i);

/**
 * Returns true if the given index represents a negative or positive
 * symbol for a number, false otherwise.
 * @param str the string.
 * @param i the index.
 * @return true if the given index represents a negative or positive
 * symbol for a number, false otherwise.
 */
int isSigned(const char *str, int i);

/**
 * Returns the precedence of the given operator.
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
int isOperator(const char *str);

/**
 * Returns true if the given string represents a function,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents a function,
 * false otherwise.
 */
int isFunction(const char *str);

/**
 * Returns true if the given string represents a trigonometric function,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents a trigonometric function,
 * false otherwise.
 */
int isTrigonometric(const char *str);

/**
 * Returns true if the given string represents a number,
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents a number,
 * false otherwise.
 */
int isNumber(const char *str);

/**
 * Returns true if the given string is a valid value
 * (function, operator or number), false otherwise.
 * @param str the string.
 * @return Returns true if the given value is a valid value,
 * false otherwise.
 */
int isValid(const char *str);

#endif /* TOKENIZER_H_ */
