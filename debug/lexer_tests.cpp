//
// Created by sc18jt on 15/02/2020.
//
#include "catch2/catch.hpp"
#include "lexer.h"

TEST_CASE("Tokenizer recognises types.", "[Tokenizer]"){
    Lexer lexer("/home/sc18jt/CLionProjects/comp2932/debug/samples/types.jack");

    Token token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "class");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "Test");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "int");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "x");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "=");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "404");
    REQUIRE(token.getType() == 3);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == ";");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "char");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "y");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "=");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "false");
    REQUIRE(token.getType() == 4);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == ";");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "boolean");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "z");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "=");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "true");
    REQUIRE(token.getType() == 0);
}

TEST_CASE("Tokenizer handles unexpected EOF.", "[Tokenizer]"){
    Lexer lexer((char *) "/home/sc18jt/CLionProjects/comp2932/debug/samples/eof.jack");
}

TEST_CASE("Lexer getNextToken() produces expected tokens.", "[Lexer]"){
    Lexer lexer("debug/samples/average.jack");

    Token token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "class");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "Main");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "function");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "void");
    REQUIRE(token.getType() == 0);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "main");
    REQUIRE(token.getType() == 1);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "(");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == ")");
    REQUIRE(token.getType() == 2);

    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);
}

TEST_CASE("Lexer peekNextToken() produce expected tokens.", "[Lexer]"){
    Lexer lexer("debug/samples/average.jack");

    Token token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "class");
    REQUIRE(token.getType() == 0);
    token = lexer.getNextToken();


    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "Main");
    REQUIRE(token.getType() == 1);
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "Main");
    REQUIRE(token.getType() == 1);

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "function");
    REQUIRE(token.getType() == 0);
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "function");
    REQUIRE(token.getType() == 0);

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "void");
    REQUIRE(token.getType() == 0);
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "void");
    REQUIRE(token.getType() == 0);

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "main");
    REQUIRE(token.getType() == 1);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "(");
    REQUIRE(token.getType() == 2);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == ")");
    REQUIRE(token.getType() == 2);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);

}