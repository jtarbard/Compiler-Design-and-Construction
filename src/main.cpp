//
// Created by sc18jt on 12/02/2020.
//

#include <dirent.h>
#include <unistd.h>
#include "main.h"
#include "lexer.h"
#include "parser.h"
using namespace std;

#define release true
#if DEBUG
release = false
#endif

int main(int argc, char* argv[]){

    if(release) {
        if (argc == 2) {
            std::string sDir = argv[1];
            DIR* file = opendir(argv[1]);

            struct dirent *ptr;;
            while((ptr = readdir(file)) != nullptr){
                std::string sFile = ptr->d_name;
                if(ptr->d_type == DT_REG && sFile.find(".jack")){
                    cout << "Opening " << sDir+"/"+sFile << endl;
                    Lexer lexer(sDir+"/"+sFile);
                    Parser parser(&lexer);
                }
            }
        }
        else {
             cerr << "Error Occurred: Directory argument not provided." << endl;
             exit(1);
        }
    }

    return 0;
}