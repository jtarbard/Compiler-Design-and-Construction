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
public:
    enum tokenType {Keyword, Symbol, Identifier, Integer, String, Boolean};
    void set_lexeme(string str);
    void set_type(tokenType type);
    string get_lexeme();
    tokenType get_type();

private:
    tokenType type;
    string lexeme;
};

class Lexer {
    const int keywordCount = 21;
    char const *keywords[21] = {
            "class","constructor","method","function", //program components
            "int","boolean","char","void", //primitive types
            "var","static","field", //variable declarations
            "let","do","if","else","while","return", //statements
            "true","false","null", //constant values
            "this" //object reference
    };
    vector<char> stream;
    vector<char>::iterator sItr;
    vector<Token> tokens;
    vector<Token>::iterator tCursor;

    void generate_tokens();

public:
    Lexer(char *arg);
    Token getNextToken();
    Token peekNextToken();
};
#endif //COMP2932_LEXER_H
