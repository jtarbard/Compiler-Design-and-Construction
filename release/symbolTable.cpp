
#include <iostream>
#include <fstream>
#include "symbolTable.h"

void Table::addSymbol(Symbol symbol) {
    if(symbol.getKind() < 4) {
        symbol.setRelAdd(relativeAddress[symbol.getKind()]);
        relativeAddress[symbol.getKind()]++;
    }
    table.push_back(symbol);
}

bool Table::findSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.getName() == name){
            return true;
        }
        else if(symbol.getKind() == Symbol::Function){
            for(auto argument : *symbol.getArgs()){
                if(argument.getName() == name){
                    return true;
                }
            }
        }
    }

    return false;
}

Symbol* Table::editSymbol(string name) {
    for(auto& symbol : table){
        if(symbol.getName() == name){
            return &symbol;
        }
        else if(symbol.getKind() == Symbol::Function){
            for(auto& argument : *symbol.getArgs()){
                if(argument.getName() == name){
                    return &argument;
                }
            }
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

void SymbolTable::display(string file) {
    Table scopes[] = {global, local};

    ofstream log;
    log.open("./debug/symbolTableLog.txt", std::ios::app);

    int i = 0;
    log << file << endl;
    for(auto scope : scopes){
        log << "-----------------------" << endl;
        if(i == 0){
            log << "Global scope at end of class:" << endl;
            i++;
        }
        else{
            log << "Local scope (the final subroutine):" << endl;
        }
        log << "-----------------------" << endl;
        for(auto g : scope.table){
            log << "Name: " << g.getName() << ", Kind: " << g.getKind();

            if(g.getKind() < 4){
                log << ", Type: " << g.getType() << ", Address: " << g.getRelAdd() << ", Init: "<< g.getInit();
            }
            else if(g.getKind() == Symbol::Function){
                log << endl << "Arguments: ";
                for(auto a : *g.getArgs()){
                    log << "Name: " << a.getName() << ", Type: " << a.getType() << ", ";
                }
            }

            log << endl;
        }
    }

    log << endl << endl;
    log.close();
}


