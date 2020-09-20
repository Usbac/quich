#ifndef QUICH_H_
#define QUICH_H_
#define OPERATION_BUFFER 512
#define VERSION_MSG "QUICH v3.0.0\n"
#define INPUT_LINE "> "
#define DEFINITION_MSG "(definition)\n"
#define STATEMENT_SEPARATOR ";"
#define CLEAR_COMMAND "clear"
#define EXIT_COMMAND "exit"
#define INIT_MSG "Running "VERSION_MSG \
    "Type '"CLEAR_COMMAND"' to clear the screen.\n" \
    "Type '"EXIT_COMMAND"' to exit the program.\n"
#define BYE_MSG "Bye...\n"
#define HELP_MSG "QUICH: Just an advanced terminal calculator\n\n" \
    "USAGE: operation [options...]\n\n" \
    "OPTIONS:\n\n" \
    "-d --degree          Manage the given angles in degrees.\n" \
    "-f --format [%%s]     The format to display the result.\n" \
    "-h --help            Show help about the software.\n" \
    "-i --interactive     Force interactive mode.\n" \
    "-p --precision [%%i]  The number of decimals used for the internal numbers.\n" \
    "-r --round [%%i]      The number of decimals to round the result.\n" \
    "-t --thousands       Display the result with thousands separators.\n" \
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
    "rand   Random number between 0 and 1.\n" \
    "round  Round to the nearest integer value.\n" \
    "floor  Round down.\n" \
    "ceil   Round up.\n\n" \
    "AVAILABLE:\n\n" \
    "Constants 'PI' (3.14...), 'E' (2.71...) and 'G' (9.80...).\n" \
    "Units of measurement for data storage 'mb', 'gb', 'tb' and 'pt' (returned in kb).\n\n"

#endif /* QUICH_H_ */
