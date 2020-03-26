//
// Created by sc18jt on 25/03/2020.
//

#include "symbol_table.h"

void Symbol::setName(string name) {
    this->name = name;
}

void Symbol::setType(Symbol::symbolType type) {
    this->type = type;
}

void Symbol::setAttributes(Symbol::symbolKind kind, int size, bool constant, vector<Symbol> args) {
    this->attributes.kind = kind;
    this->attributes.size = size;
    this->attributes.constant = constant;
    this->attributes.args = std::move(args);
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

vector<Symbol> Symbol::getArgs() {
    return this->attributes.args;
}

void Symbol_Table::addSymbol(string name, Symbol::symbolType type, Symbol::symbolKind kind, int size, bool constant, vector<Symbol> args) {
    Symbol symbol; //create symbol

    //set symbol fields
    symbol.setName(std::move(name));
    symbol.setType(type);
    symbol.setAttributes(kind, size, constant, std::move(args));

    table.push_back(symbol); //add symbol to table
}

bool Symbol_Table::findSymbol(string name) {
    vector<Symbol>::iterator tCursor;
    Symbol symbol;
    //search through symbol table
    for(tCursor = table.begin(); tCursor != table.end(); tCursor++) {
        symbol = *tCursor;
        if(symbol.getName() == name) {
            //symbol with name found
            return true;
        }
    }

    //no symbol with that name found
    return false;
}