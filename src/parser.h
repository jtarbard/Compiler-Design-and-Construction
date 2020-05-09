//
// Created by sc18jt on 04/03/2020.
//

#ifndef MYJC_PARSER_H
#define MYJC_PARSER_H

#include "lexer.h"
#include "symbolTable.h"

class Parser {
    //object instances
    Token token;
    Lexer *lexer;
    SymbolTable symbolTable;
    //general variables
    int size;
    //Error handler
    void error(string errorType, string msg);
    //Jack Grammar
    string operand();
    string factor();
    string term();
    string arithmeticExpression();
    string relationalExpression();
    string expression();
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

    //Symbol Table Actions
    void setSymbolType(Symbol* symbol);
    void setSymbolName(Symbol* symbol, Table table);

public:
    explicit Parser(Lexer *parLexer);

    void typeChecker(string oldType, string newType);

    void typeChecker(string t1);
};

#endif //MYJC_PARSER_H
