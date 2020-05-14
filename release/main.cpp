//
// Created by sc18jt on 12/02/2020.
//

#include <dirent.h>
#include <unistd.h>
#include "main.h"
#include "lexer.h"
#include "parser.h"
using namespace std;

int main(int argc, char* argv[]){

    if (argc == 2) {
        DIR* path = opendir(argv[1]);
        string sPath = argv[1];

        if(path != nullptr) {
            struct dirent *ptr;
            while((ptr = readdir(path)) != nullptr){
                std::string sFile = ptr->d_name;
                if(ptr->d_type == DT_REG && sFile.find(".jack")){
                    Lexer lexer(sPath+"/"+sFile);
                    Parser parser(&lexer);
                }
            }
        }
        else{
            cerr << "Error: Directory could not be opened." << endl;
            exit(1);
        }
    }
    else {
         cerr << "Error: Directory argument not provided." << endl;
         exit(1);
    }

    return 0;
}

