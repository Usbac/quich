#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#define BUFFER 32
#define NUMBER_FORMAT "%.15g"
#define M_PI acos(-1)
#define M_E 2.71828182845904523536
#define G 9.80665

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

typedef struct list_struct {
    struct token_struct *first;
    struct token_struct *last;
} list;

extern char *current_token;
extern enum TOKEN_TYPE current_type;

/**
 * Creates a list based on the given string
 * with infix notation.
 * @param list the list.
 * @param func the infix function.
 */
void tokenize(list *list, const char *func);

/**
 * Frees the given list.
 * @param list the list.
 */
void freeList(list *list);

/**
 * Initializes the given list.
 * @param list the list.
 */
void initList(list **list);

/**
 * Returns the type of the given char.
 * @param ch the char.
 * @return the type of the given char.
 */
enum TOKEN_TYPE getType(char ch);

/**
 * Adds a token to the given list.
 * @param list the list.
 * @param token the token string.
 */
void addToken(list *list, const char *token);

/**
 * Stores the token value into the given variable.
 * @param dest the pointer to the variable where the token
 * value will be stored.
 * @param token the token string.
 */
void getTokenVal(char **dest, const char *token);

/**
 * Process the char in the given index of the string.
 * @param list the list.
 * @param str the string.
 * @param i the index.
 */
void processChar(list *list, const char *str, int i);

/**
 * Returns true if the given char is ignorable for
 * the operation, false otherwise.
 * @return true if the given char is ignorable,
 * false otherwise.
 */
int isIgnorableChar(char ch);

/**
 * Returns true if the given index represents a negative or positive
 * symbol for a number, false otherwise.
 * @param list the list.
 * @param str the string.
 * @param i the index.
 * @return true if the given index represents a negative or positive
 * symbol for a number, false otherwise.
 */
int isSigned(list *list, const char *str, int i);

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
 * Returns true if the given string represents an
 * unit of measurement for data storage (megabyte to petabyte),
 * false otherwise.
 * @param str the string.
 * @return true if the given string represents an
 * unit of measurement for data storage,
 * false otherwise.
 */
int isDataUnit(const char *str);

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
