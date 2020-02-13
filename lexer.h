//
// Created by sc18jt on 12/02/2020.
//

#ifndef COMP2932_LEXER_H
#define COMP2932_LEXER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Token {
    enum tokenType {};
    string lexeme;
    tokenType type;

    Token(){
        lexeme = ""; //prevent inappropriate memory access
    }
};

class Lexer {
    int stream();
public:
    Lexer(char *arg);
    Token getNextToken();
    Token peekNextToken();
};
#endif //COMP2932_LEXER_H
