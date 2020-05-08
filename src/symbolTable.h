//
// Created by sc18jt on 25/03/2020.
//

#ifndef MYJC_SYMBOLTABLE_H
#define MYJC_SYMBOLTABLE_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class Table;

class Symbol {
public:
    enum symbolType {Type, Variable, Function};
    enum symbolKind {Simple, Array, Struct, Object};

    //setters
    void setName(string name);
    void setType(symbolType type);
    void setKind(symbolKind kind);
    void setSize(int size);
    void setSize(const string& size);
    void setVarType(string type);
    void setConst(bool isConst);
    void setNumArgs(int args);
    void setLocVarSize(int size);
    void setRetType(string retType);
    void setArgs(vector<Symbol> args);
    //getters
    string getName();
    symbolType getType();
    symbolKind getKind();
    int getSize();
    bool getConstant();
    vector<Symbol> getArgs();

private:
    string name;
    symbolType type;
    struct attributes {
        symbolKind kind;
        int size;
        string type;
        bool constant;
        int numArgs;
        int locVarSize;
        string return_type;
        vector<Symbol> args;
    } attributes;

};

class Table {
    vector<Symbol> table;

public:
    void addSymbol(Symbol symbol);
    bool findSymbol(string name);
    int findSymbolSize(string name);
    int getSize();
    void display();

    Symbol *editSymbol(string name);
};

class SymbolTable {
    std::list<Table> symbolTable;

public:
    void addSymbol(Symbol symbol);
    void addScope();
    void delScope();
    bool findSymbol(string name);
    int findSymbolSize(string name);
    int getSize();

    void display();

    Symbol *editSymbol(string name);
};


#endif //MYJC_SYMBOLTABLE_H
