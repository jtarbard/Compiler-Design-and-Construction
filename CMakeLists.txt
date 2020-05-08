cmake_minimum_required(VERSION 3.15)
project(myjc)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include_directories(src
            tests)

    add_executable(myjc
            src/lexer.cpp
            src/lexer.h
            src/parser.cpp
            src/parser.h
            src/symbolTable.cpp
            src/symbolTable.h
            tests/catch_main.cpp
            tests/lexer_tests.cpp
            tests/parser_tests.cpp
            )

else()
    include_directories(src)

    add_executable(myjc
            src/lexer.cpp
            src/lexer.h
            src/parser.cpp
            src/parser.h
            src/symbolTable.cpp
            src/symbolTable.h
            src/main.cpp
            src/main.h
            )
endif()