cmake_minimum_required(VERSION 3.17)
project(quich)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    pkg_search_module(LINENOISE liblinenoise)
endif()

add_executable(quich
        src/lexer.c src/lexer.h
        src/parser.c src/parser.h
        src/helper.c src/helper.h
        src/variable.c src/variable.h
        src/quich.c src/quich.h)

if(LINENOISE_FOUND)
    message(STATUS "Found linenoise: ${LINENOISE_INCLUDEDIR} (found version \"${LINENOISE_VERSION}\")")
    target_include_directories(quich PRIVATE ${LINENOISE_INCLUDE_DIRS})
    target_link_directories(quich PRIVATE ${LINENOISE_LIBRARY_DIRS})
    target_link_libraries(quich ${LINENOISE_LIBRARIES})
else()
    message(STATUS "linenoise not found, using bundled version")
    target_sources(quich PRIVATE
        lib/linenoise.c lib/linenoise.h)
    target_include_directories(quich PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

target_link_libraries(quich m)

add_executable(quich_test
        src/lexer.c src/lexer.h
        src/parser.c src/parser.h
        src/helper.c src/helper.h
        src/variable.c src/variable.h
        tests/main.c)

if(LINENOISE_FOUND)
    target_include_directories(quich_test PRIVATE ${LINENOISE_INCLUDE_DIRS})
    target_link_directories(quich_test PRIVATE ${LINENOISE_LIBRARY_DIRS})
    target_link_libraries(quich_test ${LINENOISE_LIBRARIES})
else()
    target_sources(quich_test PRIVATE
        lib/linenoise.c lib/linenoise.h)
    target_include_directories(quich_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

target_link_libraries(quich_test m)
