//
// Created by sc18jt on 25/03/2020.
//

#include <iostream>
#include "symbolTable.h"

void Symbol::setName(string name) {
    this->name = name;
}

void Symbol::setType(Symbol::symbolType type) {
    this->type = type;
}

string Symbol::getName() {
    return this->name;
}

Symbol::symbolType Symbol::getType() {
    return this->type;
}

Symbol::symbolKind Symbol::getKind() {
    return this->attributes.kind;
}

int Symbol::getSize() {
    return this->attributes.size;
}

bool Symbol::getConstant() {
    return this->attributes.constant;
}

Table* Symbol::getArgs() {
    return this->attributes.args;
}

void Symbol::setVarType(string type) {
    this->attributes.type = type;
}

void Symbol::setKind(Symbol::symbolKind kind) {
    this->attributes.kind = kind;
}

void Symbol::setSize(int size) {
    this->attributes.size = size;
}

void Symbol::setConst(bool isConst) {
    this->attributes.constant = isConst;
}

void Symbol::setArgs(Table args) {
    this->attributes.args = &args;
}

void Symbol::setRetType(string retType) {
    this->attributes.return_type = retType;
}

void Symbol::setNumArgs(int args) {
    this->attributes.numArgs = args;
}

void Symbol::setLocVarSize(int size) {
    this->attributes.locVarSize = size;
}

void Symbol::setSize(const string& size) {
    if(size == "int"){
        this->attributes.size = sizeof(int);
    }
    else if(size == "char"){
        this->attributes.size = sizeof(char);
    }
    else if(size == "boolean"){
        this->attributes.size = sizeof(bool);
    }
}


void Table::addSymbol(Symbol symbol){
    table.push_back(symbol); //add symbol to table
}

bool Table::findSymbol(string name) {
    vector<Symbol>::iterator tCursor;
    Symbol symbol;
    //search through symbol table
    for(tCursor = table.begin(); tCursor != table.end(); tCursor++) {
        symbol = *tCursor;
        if(symbol.getName() == name) {
            //symbol with name found
            return true;
        }
        else if(symbol.getType() == Symbol::Function && symbol.getArgs() != nullptr){
            Table* temp = symbol.getArgs();
            cout << "PARAMLIST" << symbol.getName() << temp->findSymbol(name);
            if(temp->findSymbol(name)){
                return true;
            }
        }
    }

    //no symbol with that name found
    return false;
}

int Table::getSize(){
    int totalSize = 0;
    Symbol symbol;
    vector<Symbol>::iterator tCursor;

    for(tCursor = this->table.begin(); tCursor != this->table.end(); tCursor++) {
        symbol = *tCursor;
        totalSize = totalSize + symbol.getSize();
    }
}

void Table::display() {
    vector<Symbol>::iterator tCursor;
    Symbol symbol;
    //search through symbol table
    for(tCursor = table.begin(); tCursor != table.end(); tCursor++) {
        symbol = *tCursor;
        cout << "Name: " << symbol.getName() << ", Type " << symbol.getType() << endl;
    }
}

int Table::findSymbolSize(string name) {
    vector<Symbol>::iterator tCursor;
    Symbol symbol;
    //search through symbol table
    for(tCursor = table.begin(); tCursor != table.end(); tCursor++) {
        symbol = *tCursor;
        if(symbol.getName() == name) {
            //symbol with name found
            return symbol.getSize();
        }
    }

    return -1;
}

void SymbolTable::addSymbol(Symbol symbol) {
    symbolTable.back().addSymbol(symbol);
    cout << symbol.getName() << symbol.getType() << endl; //todo remove
}

bool SymbolTable::findSymbol(string name) {
    for(auto table : symbolTable){
        if(table.findSymbol(name)){
            return true;
        }
    }
    return false;
}

int SymbolTable::getSize() {
    return symbolTable.back().getSize();
}

void SymbolTable::addScope() {
    symbolTable.emplace_back();
}

void SymbolTable::delScope() {
    if(symbolTable.size() > 1) {
        symbolTable.pop_back();
    }
}

void SymbolTable::display() {
    printf("SYMBOL:");
    for(auto table : symbolTable){
        table.display();
    }
}

int SymbolTable::findSymbolSize(string name) {
    int size;
    for(auto table : symbolTable){
        size = table.findSymbolSize(name);
        if( size != -1){
            return size;
        }
    }

    return -1;
}
