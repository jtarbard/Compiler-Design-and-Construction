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

Lexer::Lexer(char *arg) {
    file;
    file.open(arg);

    if(file){
        scanner();
        tokenizer();
    }
    else{ //file invalid
        cerr << "Error Occurred: File could not be opened." << endl;
        exit(1);
    }
}

void Lexer::scanner(){
    char c;
    while (file >> noskipws >> c) {
        stream.push_back(c);
    }
    stream.push_back(EOF);
}

void Lexer::tokenizer(){
    Token token;
    string str;

    for(sItr = stream.begin(); sItr != stream.end(); sItr++) {
        //whitespace
        if (isspace(*sItr) != 0) {} //consume
        //alphabetical character
        else if (isalpha(*sItr) != 0){
            //iterate while alphanumeric
            for(; sItr != stream.end() && (isalpha(*sItr)||isalnum(*sItr)); sItr++){
                str.push_back(*sItr);
            }
            sItr--; //needed to prevent over-consumption
            token.setLexeme(str);
            //determine type
            if (!str.find_first_of("0123456789") == string::npos) { //alphanumeric
                token.setType(Token::Identifier);
            }
            else if (str.compare("true") == 0 || str.compare("false") == 0) {
                token.setType(Token::Boolean);
            }
            else { //alphabetic
                token.setType(Token::Identifier); //default to id
                for (int i = 0; i < keywordCount; i++) {
                    if (str.compare(keywords[i]) == 0) {
                        token.setType(Token::Keyword); //update to keyword
                        break;
                    }
                }
            }
            //clean up
            str.erase();
            //store token
            tokens.push_back(token);
        }
        //integer
        else if(isdigit(*sItr) != 0){
            for(; sItr != stream.end() && isalnum(*sItr); sItr++){
                str.push_back(*sItr);
            }
            sItr--;
            //set token info
            token.setType(Token::Integer);
            token.setLexeme(str);
            tokens.push_back(token);
            str.erase();
        }
        //symbol
        else if(ispunct(*sItr) != 0){
            auto itr = sItr;
            itr++;
            if(*sItr == '/' && *itr == '/'){
                while(*sItr != '\n' && *sItr != '\r' && sItr != stream.end() && *sItr != EOF ){
                    sItr++; //consume
                }
            }
            else if(*sItr == '/' && *itr == '*'){
                while(((*sItr != '*' || *itr != '/') && itr != stream.end() && *itr != EOF)){
                    sItr++; //consume
                    itr++; //consume
                }
                sItr++; //needed to consume end /
            }
            else if(*sItr == '\"'){
                for(; itr != stream.end() && *itr != EOF && *itr != '\"'; itr++, sItr++){
                    str.push_back(*itr);
                }
                sItr++; //consume end "
                token.setLexeme(str);
                token.setType(Token::String);
                str.erase();
                tokens.push_back(token);

            }
            //symbol
            else{
                //set lexeme
                str.push_back(*sItr);
                token.setLexeme(str);
                str.erase();
                //set type
                token.setType(Token::Symbol);
                //store token
                tokens.push_back(token);
            }
        }
        else if(*sItr == EOF){
            token.setLexeme("");
            token.setType(Token::eof);
            tokens.push_back(token);
        }
        else if(*sItr == '\n'){
            lineNum++;
        }
        //error
        else{
            cerr << "Error Occurred: Character of unsupported type." << endl;
            cout << "Character: " << *sItr << endl;
        }
    }
    //Tokenizing complete
    tCursor = tokens.begin();
}

Token Lexer::getNextToken() {
    Token token;
    if (!tokens.empty()){
        token = *tCursor;
        tCursor++;
    }
    return token;
}

Token Lexer::peekNextToken() {
    Token token;
    if (!tokens.empty()) {
        if (tCursor++ != tokens.end()) {
            token = *tCursor;
            tCursor--;
        }
    }
    return token;
}
