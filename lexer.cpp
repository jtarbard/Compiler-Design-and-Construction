//
// Created by sc18jt on 12/02/2020.
//

#include "lexer.h"

Lexer::Lexer(char *arg) {
    ifstream file;
    file.open(arg);

    if(file){
        char c;
        while (file >> noskipws >> c) {
            stream.push_back(c);
        }
        file.close();
    }
    else{ //file invalid
        cerr << "Error Occurred: File could not be opened." << endl;
        exit(1);
    }
}
