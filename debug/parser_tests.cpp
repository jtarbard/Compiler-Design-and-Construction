//
// Created by sc18jt on 04/03/2020.
//
#include "catch2/catch.hpp"
#include "main.h"
#include "lexer.h"
#include "parser.h"

TEST_CASE("Parser does not throw error on valid file - custom"){
//debug file reset
remove("debug/symbolTableLog.txt");
remove("debug/tokensLog.txt");

Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/debug/samples/custom.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - parser"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/parser.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - fraction"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/fraction.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - hello world"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/hello_world.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - square"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/square.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - arrays"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/arrays.jack");
Parser parser(&lexer);
}

TEST_CASE("Parser does not throw error on valid file - average"){
Lexer lexer( "/home/sc18jt/CLionProjects/comp2932/debug/samples/average.jack");
Parser parser(&lexer);
}