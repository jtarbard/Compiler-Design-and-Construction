//
// Created by sc18jt on 12/02/2020.
//

#include "lexer.h"

void Token::set_lexeme(string str) {
    this->lexeme = str;
}

string Token::get_lexeme() {
    return this->lexeme;
}

void Token::set_type(Token::tokenType type) {
    this->type = type;
}

Token::tokenType Token::get_type() {
    return this->type;
}

Lexer::Lexer(char *arg) {
    ifstream file;
    file.open(arg);

    if(file){
        char c;
        while (file >> noskipws >> c) {
            stream.push_back(c);
        }
        file.close();

        generate_tokens();
    }
    else{ //file invalid
        cerr << "Error Occurred: File could not be opened." << endl;
        exit(1);
    }
}

void Lexer::generate_tokens(){
    Token token;
    string str;

    for(sItr = stream.begin(); sItr != stream.end(); sItr++) {
        //whitespace
        if (isspace(*sItr) != 0) {
            //consume
        }
        //character
        else if (isalpha(*sItr) != 0) {
            for (auto itr = sItr; itr != stream.end(); itr++) {
                //end of alphanumeric
                if (!(isalpha(*itr) != 0 || isdigit(*itr) != 0)) {
                    token.set_type(Token::Identifier);
                    //if keyword or boolean overwrite
                    if (str.find_first_of("0123456789") == string::npos) {
                        for (int i = 0; i < keywordCount; i++) {
                            if (str.compare(keywords[i]) == 0) {
                                token.set_type(Token::Keyword);
                            }
                            else if(str.compare("true") == 0 || str.compare("false") == 0){
                                token.set_type(Token::Boolean);
                            }
                        }
                    }
                    token.set_lexeme(str);
                    tokens.push_back(token);
                    str.erase();
                    sItr = --itr;
                    break;
                }
                //add character
                else{
                    str.push_back(*itr);
                }
            }
        }
        //integer
        else if(isdigit(*sItr) != 0){
            for(auto itr = sItr; itr != stream.end(); itr++){
                //end of integer
                if(isdigit(*itr) == 0){
                    //set lexeme
                    token.set_lexeme(str);
                    //set type
                    token.set_type(Token::Integer);
                    //store token
                    tokens.push_back(token);
                    //update iterator
                    str.erase();
                    sItr = itr;
                    break;
                }
                //add digit
                else{
                    str.push_back(*itr);
                }
            }
        }
        //symbol
        else if(ispunct(*sItr) != 0){
            auto itr = sItr;
            itr++;
            if(itr != stream.end()){
                //single line comment
                if(*sItr == '/' && *itr == '/'){
                    while(*itr != '\n' && *itr != '\r' && itr != stream.end()){
                        itr++; //consume
                    }
                    sItr = itr;
                }
                //multi line or api comment
                else if(*sItr == '/' && *itr == '*'){
                    while(itr != stream.end()){
                        if(*itr == '*' && itr++ != stream.end()){
                            if(*itr == '/'){
                                break;
                            }
                        }
                        itr++; //consume
                    }
                    sItr = itr;
                }
                //string
                else if(*sItr == '"'){
                    sItr++;
                    while(sItr != stream.end() && *sItr != '"'){
                        str.push_back(*sItr);
                        sItr++;
                    }
                    //set type
                    token.set_type(Token::String);
                    //set lexeme
                    token.set_lexeme(str);
                    //
                    tokens.push_back(token);
                    str.erase();

                }
                //symbol
                else{
                    //set lexeme
                    token.set_lexeme(string (1,*sItr));
                    //set type
                    token.set_type(Token::Symbol);
                    //store token
                    tokens.push_back(token);
                }
            }
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
    Token token = *tCursor;
    tCursor++;
    return token;
}

Token Lexer::peekNextToken() {
    Token token;
    if(tCursor++ != tokens.end()){
        token = *tCursor;
        tCursor--;
    }
    return token;
}
