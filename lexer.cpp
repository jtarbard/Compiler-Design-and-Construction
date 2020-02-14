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

Lexer::Lexer(char *arg) {
    ifstream file;
    file.open(arg);

    if(file){
        char c;
        while (file >> noskipws >> c) {
            stream.push_back(c);
        }
        file.close();

        sCursor = stream.begin();
        generate_tokens();
    }
    else{ //file invalid
        cerr << "Error Occurred: File could not be opened." << endl;
        exit(1);
    }
}

void Lexer::generate_tokens(){
    for(sCursor; sCursor != stream.end(); sCursor++){
        //whitespace
        if(isspace(*sCursor)){
            for(sCursor; sCursor != stream.end(); sCursor++){
                if(!isspace(*sCursor)){ //end of whitespaces
                    //TODO: delimit?
                }
            }
        }
        //character
        else if(isalpha(*sCursor)){
            for(sCursor; sCursor != stream.end(); sCursor++){
                if(!(isalpha(*sCursor) || isdigit(*sCursor))){ //end of alphanumeric
                    any_of(str.begin(), str.end(), ::isdigit); //does string contain digit
                }
            }
        }
        //integer
        else if(isdigit(*sCursor)){

        }
        //symbol
        else if(ispunct(*sCursor)){

        }
        //error
        else{
            cerr << "Error Occurred: Character of unsupported type." << endl;
            exit(1);
        }
    }
}

Token Lexer::getNextToken() {
//    Token token = *tCursor;
//    tCursor++;
    return Token();
}

Token Lexer::peekNextToken() {
    return Token();
}
