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
    enum tokenType {Keyword, Identifier, Symbol, Integer, String, eof};

    void setLexeme(string str);
    void setType(tokenType type);
    void setLine(int ln);
    string getLexeme();
    tokenType getType();
    int getLine();

private:
    tokenType type;
    string lexeme;
    int line;
};

class Lexer {
    ifstream file;
    char const *keywords[21] = {
            "class","constructor","method","function", //program components
            "int","boolean","char","void", //primitive types
            "var","static","field", //variable declarations
            "let","do","if","else","while","return", //statements
            "true","false","null", //constant values
            "this" //object reference
    };
    int const keywordsSize = 21;
    //
    vector<char> stream;
    vector<Token> tokens;
    vector<Token>::iterator tCursor;
    string fileName;

    void scanner();
    void tokenizer();

public:
    Lexer(char *arg);
    Token getNextToken();
    Token peekNextToken();
    string getFileName(){return fileName;}
};
#endif //COMP2932_LEXER_H
