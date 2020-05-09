//
// Created by sc18jt on 04/03/2020.
//
#include "catch2/catch.hpp"
#include "lexer.h"
#include "parser.h"

//TEST_CASE("Parser does not throw error on valid file - custom"){
//Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/custom.jack");
//Parser parser(&lexer);
//}

TEST_CASE("Parser does not throw error on valid file - parser"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/parser.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - fraction"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/fraction.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - hello world"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/hello_world.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - square"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/square.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - arrays"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/arrays.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - average"){
Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/tests/samples/average.jack");
Parser parser(&lexer);
}