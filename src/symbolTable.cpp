
#include "symbolTable.h"

void SymbolTable::addSymbol(Symbol symbol) {
    table.push_back(symbol);
}

bool SymbolTable::findSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.name == name){
            return true;
        }
    }

    return false;
}
