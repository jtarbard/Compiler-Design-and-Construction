
#include <iostream>
#include "symbolTable.h"

void Table::addSymbol(Symbol symbol) {
    if(symbol.getKind() < 4) {
        symbol.setRelAdd(relativeAddress[symbol.getKind()]);
        this->relativeAddress[symbol.getKind()]++;
    }
    table.push_back(symbol);
}

bool Table::findSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.getName() == name){
            return true;
        }
    }

    return false;
}

Symbol* Table::editSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.getName() == name){
            return &symbol;
        }
    }

    return nullptr;
}

SymbolTable::SymbolTable() {
    global = Table();
    local = Table();
}

bool SymbolTable::findSymbol(string name) {
    return global.findSymbol(name) || local.findSymbol(name);
}

Symbol* SymbolTable::editSymbol(string name) {
    Symbol* g = global.editSymbol(name);
    Symbol* l =local.editSymbol(name);

    if(g != nullptr){
        return g;
    }
    else if(l != nullptr){
        return l;
    }
    else{
        return nullptr;
    }
}

void SymbolTable::display() {
    Table scopes[] = {global, local};
    int i = 0;
    for(auto scope : scopes){
        cout << "-----------------------" << endl;
        if(i == 0){
            cout << "Global scope:" << endl;
            i++;
        }
        else{
            cout << "Local scope:" << endl;
        }
        cout << "-----------------------" << endl;
        for(auto g : scope.table){
            cout << "Name: " << g.getName() << ", Type: " << g.getType() << ", Kind: " << static_cast<Symbol::symbolKind>(g.getKind())
            << ", Address: " << g.getRelAdd() << ", Init: "<< g.getInit() << endl;
        }
    }

}


