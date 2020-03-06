//
// Created by sc18jt on 04/03/2020.
//

#ifndef MYJC_PARSER_H
#define MYJC_PARSER_H

#include "lexer.h"

class Parser {
    Token token;
    Lexer *lexer;
    //Error handler
    void error(string msg);
    //Jack Grammar
    void operand();
    void factor();
    void term();
    void arithmeticExpression();
    void relationalExpression();
    void expression();
    void returnStatement();
    void expressionList();
    void subroutineCall();
    void doStatement();
    void whileStatement();
    void ifStatement();
    void letStatement();
    void varDeclareStatement();
    void statement();
    void subroutineBody();
    void paramList();
    void subroutineDeclare();
    void type();
    void classVarDeclare();
    void memberDeclare();
    void classDeclare();

    //Jack Grammar Rule Checkers
    bool isOperand();
    bool isFactor();
    bool isTerm();
    bool isArithmeticExpression();
    bool isRelationalExpression();
    bool isExpression();
    bool isSubroutineCall();
    bool isStatement();
public:
    explicit Parser(Lexer *parLexer);
};

#endif //MYJC_PARSER_H
