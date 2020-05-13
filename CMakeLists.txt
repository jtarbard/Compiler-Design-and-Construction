cmake_minimum_required(VERSION 2.8)
project(myjc)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include_directories(release
            debug)

    add_executable(myjc
            release/lexer.cpp
            release/lexer.h
            release/parser.cpp
            release/parser.h
            release/symbolTable.cpp
            release/symbolTable.h
            debug/catch_main.cpp
            debug/lexer_tests.cpp
            debug/parser_tests.cpp
            )

else()
    include_directories(release)

    add_executable(myjc
            release/lexer.cpp
            release/lexer.h
            release/parser.cpp
            release/parser.h
            release/symbolTable.cpp
            release/symbolTable.h
            release/main.cpp
            release/main.h
            )
endif()