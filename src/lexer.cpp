//
// Created by sc18jt on 12/02/2020.
//

#include "lexer.h"

void Token::setLexeme(string str) {
    this->lexeme = str;
}

string Token::getLexeme() {
    return this->lexeme;
}

void Token::setType(Token::tokenType type) {
    this->type = type;
}

Token::tokenType Token::getType() {
    return this->type;
}

void Token::setLine(int ln) {
    this->line = ln;
}

int Token::getLine() {
    return this->line;
}

/**
 * Constructs the Lexer object initialising attributes file,
 * stream and tokens.
 *
 * Initialises the file attribute and tries to open the file.
 * Calls scanner method to populate stream and then calls
 * tokenizer to populate tokens.
 *
 * @param arg   The filepath to the jack program to be compiled.
 */

Lexer::Lexer(char *arg) {
    file.open(arg);

    if(file){
        scanner();
        tokenizer();
        tCursor = tokens.begin();
    }
    else{ //file invalid
        cerr << "Error Occurred: File could not be opened." << endl;
        exit(1);
    }
}

/**
 * Populates Lexer's stream vector with file contents.
 *
 * Reads Lexer's file per character pushing each character
 * to the back of the Lexer's stream vector.
 */
void Lexer::scanner(){
    char c;
    while (file >> noskipws >> c) {
        stream.push_back(c);
    }
    stream.push_back(EOF); //push EOF as it's not captured by while
}

/**
 * Generates tokens from the stream vector and stores them
 * in the token vector.
 *
 * Iterates over stream vector categorising the iterate value
 * into one of five states: whitespace, alphabetical,
 * numerical, symbol, or end of file. Stream is then handled
 * internally until a delimiter is reached and the token lexeme
 * and type can be set. Tokens are then pushed to the back of
 * the tokens vector.
 */
void Lexer::tokenizer(){
    vector<char>::iterator sItr;
    int lnNum = 1;

    Token token;
    string str;
    Token::tokenType type;

    for(sItr = stream.begin(); sItr != stream.end(); sItr++) {

        //STATE: Whitespace
        if (isspace(*sItr) != 0) {
            //if newline increment line number
            if(*sItr == '\n' || *sItr == '\r'){lnNum++;}
        }

        //STATE: Alphabetical
        else if (isalpha(*sItr) != 0){
            //add to string while alphanumerical
            for(; sItr != stream.end() && (isalpha(*sItr)||isalnum(*sItr)); sItr++){
                str.push_back(*sItr);
            }
            sItr--; //prevent over-consumption
            type = Token::Identifier;

            //check if keyword
            for (int i = 0; i < keywordsSize; i++) {
                if (str.compare(keywords[i]) == 0) {
                    type = Token::Keyword;
                    break;
                }
            }
        }

        //STATE: Numerical
        else if(isdigit(*sItr) != 0){
            //add to string while numerical
            for(; sItr != stream.end() && isalnum(*sItr); sItr++){
                str.push_back(*sItr);
            }
            sItr--; //prevent over-consumption
            type = Token::Integer;
        }

        //STATE: Symbol
        else if(ispunct(*sItr) != 0){
            auto itr = sItr;
            itr++;

            //STATE: Single-line comment
            if(*sItr == '/' && *itr == '/'){
                //consume while no new line
                for(;*sItr != '\n' && *sItr != '\r' && sItr != stream.end() && *sItr != EOF; sItr++){}
                lnNum++;
            }

            //STATE: Multi-line comment
            else if(*sItr == '/' && *itr == '*'){
                //consume while no end of multi-line comment
                for(;((*sItr != '*' || *itr != '/') && itr != stream.end() && *itr != EOF); sItr++, itr++){
                    if(*sItr == '\n' || *sItr == '\r'){lnNum++;}
                }
                sItr++; //needed to consume end '/'
            }

            //STATE: String
            else if(*sItr == '\"'){
                //add to string while no end of comment
                for(; itr != stream.end() && *itr != EOF && *itr != '\"'; itr++, sItr++){
                    str.push_back(*itr);
                }
                sItr++; //consume end '"'
                type = Token::String;

            }

            //STATE: Symbol
            else{
                str.push_back(*sItr);
                type = Token::Symbol;
            }
        }

        //STATE: End of file
        else if(*sItr == EOF){
            type = Token::eof;
        }
        //STATE: Error
        else{
            cerr << "Line: " << lnNum << " Error Occurred: Character of unsupported type." << endl;
            cout << "Character: " << *sItr << endl;
            exit(1);
        }

        //STATE: Final state - create token
        if(!str.empty() || type == Token::eof){
            //Lexeme - str
            token.setLexeme(str);
            str.erase(); //reset string
            //Type - type
            token.setType(type);
            type = Token::Keyword; //reset type
            //Line - int
            token.setLine(lnNum);
            //Push token
            tokens.push_back(token);
        }
    }
}

/**
 * Returns the next token with consumption.
 */
Token Lexer::getNextToken() {
    Token token;
    if(tCursor != tokens.end()){
        token = *tCursor;
        tCursor++;
        return token;
    }
    else{
        cerr << "Error Occurred: No next token exists, reached end of token vector.";
        exit(1);
    }
}

/**
 * Returns the next token without consumption.
 */
Token Lexer::peekNextToken() {
    Token token;
    if(tCursor != tokens.end()){
        token = *tCursor;
        return token;
    }
    else{
        cerr << "Error Occurred: No next token exists, reached end of token vector.";
        exit(1);
    }
}
