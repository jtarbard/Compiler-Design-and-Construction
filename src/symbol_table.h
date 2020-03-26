//
// Created by sc18jt on 25/03/2020.
//

#ifndef MYJC_SYMBOL_TABLE_H
#define MYJC_SYMBOL_TABLE_H

#include <string>
#include <vector>
using namespace std;

class Symbol {
public:
    enum symbolType {Type, Variable, Function};
    enum symbolKind {Simple, Array, Struct};

    //setters
    void setName(string name);
    void setType(symbolType type);
    void setAttributes(symbolKind kind, int size, bool constant, vector<Symbol> args);
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
        bool constant;
        vector<Symbol> args;
    };

};

class Symbol_Table {
    vector<Symbol> table;
    //TODO: evaluate if count necessary
    int count = 0;

public:
    void addSymbol(string name, Symbol::symbolType type, Symbol::symbolKind kind, int size, bool constant, vector<Symbol> args);
    bool findSymbol(string name);
};


#endif //MYJC_SYMBOL_TABLE_H
