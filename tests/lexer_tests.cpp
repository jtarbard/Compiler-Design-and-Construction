//
// Created by sc18jt on 15/02/2020.
//
#include "catch2/catch.hpp"
#include "lexer.h"

TEST_CASE("Tokenizer recognises all types.", "[Token]"){
    Lexer lexer("./tests/samples/types.jack");

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
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "404");
    REQUIRE(token.getType() == 3);

    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "false");
    REQUIRE(token.getType() == 4);

    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    token = lexer.getNextToken();
    REQUIRE(token.getLexeme() == "true");
    REQUIRE(token.getType() == 5);

}

TEST_CASE("Tokenizer getNextToken() produce expected tokens.", "[Token]"){
    Lexer lexer("./tests/samples/main.jack");

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

TEST_CASE("Tokenizer peekNextToken() produce expected tokens.", "[Token]"){
    Lexer lexer("./tests/samples/main.jack");

    Token token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "Main");
    REQUIRE(token.getType() == 1);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "{");
    REQUIRE(token.getType() == 2);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "function");
    REQUIRE(token.getType() == 0);
    token = lexer.getNextToken();

    token = lexer.peekNextToken();
    REQUIRE(token.getLexeme() == "void");
    REQUIRE(token.getType() == 0);
    token = lexer.getNextToken();

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