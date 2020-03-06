//
// Created by sc18jt on 04/03/2020.
//

#ifndef MYJC_PARSER_H
#define MYJC_PARSER_H

#include "lexer.h"

class Parser {
    Token token;
    Lexer *lexer;
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

public:
    Parser(Lexer *parLexer);
    void error();

    void error(string msg);

    bool isOperand();

    bool isFactor();

    bool isTerm();

    bool isArithmeticExpression();

    bool isRelationalExpression();

    bool isExpression();

    bool isReturnStatement();

    bool isExpressionList();

    bool isSubroutineCall();

    bool isStatement();
};

#endif //MYJC_PARSER_H
