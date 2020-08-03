#ifndef HELPER_H_
#define HELPER_H_
#define ERROR_MEM_MSG "Error: Could not allocate memory\n"

#include <stdbool.h>

/**
 * The functions defined here are general helper functions
 * that aren't related to any specific module of this software.
 */

/**
 * Just a safer malloc function.
 * @param size the memory to allocate.
 */
void *malloc_(const size_t size);

/**
 * Just a safer strncpy function.
 * @param dest the destination string.
 * @param src the source string.
 * @param n the number of characters to copy
 * @return the number of characters to copy.
 */
int strncpy_(char *dest, const char *src, const size_t n);

/**
 * Returns the number rounded to the given digits.
 * @param n the number.
 * @param digits the digits to round after the decimal point.
 * @return the number rounded.
 */
double round_(double n, const size_t digits);

/**
 * Returns the double value of the giving string.
 * @param str the string.
 * @return the double value of the giving string.
 */
double strToDouble(const char *str);

/**
 * Adds thousands separators to the given
 * string.
 * @param str the string.
 */
void addThousandsSep(char *str);

/**
 * Returns the factorial of the giving number.
 * @param n the number.
 * @return the factorial of the giving number.
 */
long int fact(long int n);

/**
 * Reads a line from the stdin.
 * @param str the string to display when reading the input.
 * @param buffer the string where the input will be stored.
 * @param size the input size to store.
 */
void getLine(const char *str, char *buffer, size_t size);

/**
 * Adds a char to the given string
 * @param str the string.
 * @param ch the char to append to the string.
 * @param begin true for adding to the beginning, false
 * for adding to the end.
 */
void addChar(char **str, const char ch, int begin);

/**
 * Returns true if the given string is empty,
 * false otherwise.
 * @param str the string
 * @return true if the given string is empty,
 * false otherwise.
 */
bool isEmpty(const char *str);

/**
 * Calls the function to clear the screen.
 */
void clearScreen(void);

#if defined(_WIN32) || defined(WIN32)
/**
 * Reference to the snprintf function of the stdio library.
 * Because you know, some compilers are not compliant with
 * the C standard.
 */
int snprintf(char *buf, size_t size, const char *fmt, ...);
#endif

#endif /* HELPER_H_ */
