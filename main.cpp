//
// Created by sc18jt on 12/02/2020.
//

#include "main.h"
#include "lexer.h"

int main(int argc, char* argv[]){

    if(argc == 2) {
        Lexer lexer(argv[1]);
        lexer.getNextToken();
    }
    else{
        cerr << "Error Occurred: File argument not provided.";
        exit(1);
    }

    return 0;
}