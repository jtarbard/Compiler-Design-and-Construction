//
// Created by sc18jt on 12/02/2020.
//

#include "main.h"
#include "lexer.h"
using namespace std;

#define release true
#if DEBUG
release = false
#endif

int main(int argc, char* argv[]){

    if(release) {
        if (argc == 2) {
            Lexer lexer(argv[1]);
        }
        else {
             cerr << "Error Occurred: File argument not provided." << endl;
             exit(1);
        }
    }

    return 0;
}