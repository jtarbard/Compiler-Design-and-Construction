//
// Created by sc18jt on 04/03/2020.
//
#include "catch2/catch.hpp"
#include "lexer.h"
#include "parser.h"

TEST_CASE("Parser does not throw error on valid file - parser"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/parser.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - fracion"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/fraction.jack");
Parser parser(&lexer);
}