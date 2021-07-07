#ifndef QUICH_H_
#define QUICH_H_
#define MSG_VERSION "QUICH v4.0.0\n"
#define MSG_DEFINITION "(definition)\n"
#define EXIT_COMMAND "exit"
#define MSG_INIT "Running "MSG_VERSION \
    "Type '"EXIT_COMMAND"' to exit the program.\n"
#define MSG_BYE "Bye...\n"
#define MSG_HELP "QUICH: Just an advanced terminal calculator\n\n" \
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
    "Constants 'PI' (3.14...), 'E' (2.71...), 'GR' (1.61...) and 'G' (9.80...).\n" \
    "Units of measurement for data storage 'mb', 'gb', 'tb' and 'pt' (returned in kb).\n\n"

#endif /* QUICH_H_ */
