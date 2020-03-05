//
// Created by sc18jt on 04/03/2020.
//
#include "catch2/catch.hpp"
#include "lexer.h"
#include "parser.h"

TEST_CASE("Parser does not throw error on valid file."){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/average.jack");
Parser parser(&lexer);
}