//
// Created by sc18jt on 25/03/2020.
//

#ifndef MYJC_SYMBOLTABLE_H
#define MYJC_SYMBOLTABLE_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class SymbolTable;

class Symbol {

public:

    enum symbolKind {Field, Static, Local, Argument};

    string name;
    Symbol* type;
    symbolKind kind;
    int relativeAddress;
};

class Table {
public:
    vector<Symbol> table;

    int relativeAddress[4] = {
            0, //Field
            0, //Static
            0, //Local
            0 //Argument
    };

    Table()= default;;

    void addSymbol(Symbol symbol);
    Symbol* editSymbol(string name);

    virtual bool findSymbol(string name);
    void clearTable();

};

class SymbolTable : public Table {
public:
    SymbolTable();

    Table global;
    Table local;

    bool findSymbol(string name);
    void display();

};

#endif //MYJC_SYMBOLTABLE_H
