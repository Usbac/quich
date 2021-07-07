cmake_minimum_required(VERSION 3.9)
project(quich)

set(CMAKE_CXX_STANDARD 11)

add_executable(quich
        lib/linenoise.c lib/linenoise.h
        src/lexer.c src/lexer.h
        src/parser.c src/parser.h
        src/helper.c src/helper.h
        src/variable.c src/variable.h
        src/quich.c src/quich.h)

target_link_libraries(quich m)

add_executable(quich_test
        lib/linenoise.c lib/linenoise.h
        src/lexer.c src/lexer.h
        src/parser.c src/parser.h
        src/helper.c src/helper.h
        src/variable.c src/variable.h
        tests/main.c)

target_link_libraries(quich_test m)
