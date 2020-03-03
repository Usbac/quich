#ifndef MAIN_H_
#define MAIN_H_
#define OPEATION_BUFFER 512
#define VERSION_MSG "QUICH v1.0.0\n"
#define EXIT_COMMAND "exit"
#define HELP_MSG "QUICH: Just an advanced terminal calculator\n\n" \
    "USAGE: operation [options...]\n\n" \
    "OPTIONS:\n\n" \
    "-h --help            Show help about the software.\n" \
    "-p --precision [%%i]  The number of decimals used for the numbers.\n" \
    "-r --round [%%i]      The number of decimals to round the result.\n" \
    "-vvv --verbose       Display the result with details.\n" \
    "-v --version         Show the version.\n\n" \
    "FUNCTIONS:\n\n" \
    "sqrt   Square root.\n" \
    "abs    Absolute value (positive).\n" \
    "log    Natural logarithm.\n" \
    "sin    Sine trigonometric function.\n" \
    "cos    Cosine trigonometric function.\n" \
    "tan    Tangent trigonometric function.\n" \
    "floor  Round down.\n" \
    "ceil   Round up.\n"


/**
 * Prints the result of the given infix function.
 * @param str the infix function.
 */
void print(char *func);

/**
 * Prints the details of the given function.
 */
void printVerbose(void);

/**
 * Map all the arguments.
 * @param argc the number of arguments.
 * @param argv the arguments array.
 * @return 1 if the normal program flow
 * must be stopped after this function, 0 otherwise.
 */
int mapArgs(int argc, char *argv[]);

/**
 * Display the help message.
 */
void printHelp(void);

/**
 * Reads operations constantly from the stdin
 * until the 'exit' word is typed.
 * @return 0 in case of exiting successfully
 * or 1 in case of errors/exiting abruptly.
 */
int read(void);

/**
 * Just the Main function
 */
int main(int argc, char* argv[]);

#endif /* MAIN_H_ */
