cmake_minimum_required(VERSION 2.8)
project(myjc)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()

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
