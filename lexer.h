//
// Created by sc18jt on 12/02/2020.
//

#ifndef COMP2932_LEXER_H
#define COMP2932_LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Token {
    enum tokenType {Keyword, Symbol, Identifier, Integer, String, Boolean};
    string lexeme;
    tokenType type;

public:
    void set_lexeme(string str);
    string get_lexeme();

};

class Lexer {
    char *keywords = {""};
    vector<char> stream;
    vector<char>::iterator sCursor;
    vector<Token> tokens;
    vector<Token>::iterator tCursor;

    void generate_tokens();
public:
    Lexer(char *arg);
    Token getNextToken();
    Token peekNextToken();
};
#endif //COMP2932_LEXER_H
