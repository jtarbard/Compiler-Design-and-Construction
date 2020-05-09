
#include <iostream>
#include "symbolTable.h"

void Table::addSymbol(Symbol symbol) {
    symbol.relativeAddress = relativeAddress[symbol.kind];
    this->relativeAddress[symbol.kind]++;
    table.push_back(symbol);
}

bool Table::findSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.name == name){
            return true;
        }
    }

    return false;
}

Symbol* Table::editSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.name == name){
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
        for(const auto& g : scope.table){
            cout << "Name: " << g.name << ", Type: " << g.type << ", Kind: " << static_cast<Symbol::symbolKind>(g.kind)
            << ", Address: " << g.relativeAddress << ", Init: "<< g.isInitialised << endl;
        }
    }

}


