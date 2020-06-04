#ifndef MAIN_H_
#define MAIN_H_
#define OPERATION_BUFFER 512
#define VERSION_MSG "QUICH v2.3\n"
#define EXIT_COMMAND "exit"
#define INIT_MSG "Running "VERSION_MSG \
    "You can enter '"EXIT_COMMAND"' at any time to exit the program...\n"
#define BYE_MSG "Bye...\n"
#define HELP_MSG "QUICH: Just an advanced terminal calculator\n\n" \
    "USAGE: operation [options...]\n\n" \
    "OPTIONS:\n\n" \
    "-d --degree          Manage the given angles in degrees.\n" \
    "-h --help            Show help about the software.\n" \
    "-i --interactive     Force interactive mode.\n" \
    "-p --precision [%%i]  The number of decimals used for the internal numbers.\n" \
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
    "asin   Arc sine trigonometric function.\n" \
    "acos   Arc cosine trigonometric function.\n" \
    "atan   Arc tangent trigonometric function.\n" \
    "round  Round to the nearest integer value.\n" \
    "floor  Round down.\n" \
    "ceil   Round up.\n\n" \
    "AVAILABLE:\n\n" \
    "Constants 'PI' and 'E'.\n" \
    "Units of measurement for data storage mb, gb, tb and pt (returned in kb).\n\n"


/**
 * Prints the result of the given infix function.
 * @param str the infix function.
 */
void printResult(char *func);

/**
 * Prints the details of the given function.
 */
void printVerbose(void);

/**
 * Map all the arguments.
 * @param argc the number of arguments.
 * @param argv the arguments array.
 * @return true if the normal program flow
 * must be stopped after this function, false otherwise.
 */
int mapArgs(int argc, char *argv[]);

/**
 * Display the help message.
 */
void printHelp(void);

/**
 * Reads operations constantly from the stdin
 * until the 'exit' word is typed.
 * @return false in case of exiting successfully
 * or true in case of errors/exiting abruptly.
 */
int interactive(void);

/**
 * Reads a single operation from the stdin
 * and prints its result
 * @return false in case of exiting successfully
 * or true in case of errors/exiting abruptly.
 */
int processLine(void);

/**
 * Just the Main function
 */
int main(int argc, char* argv[]);

#endif /* MAIN_H_ */
