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

    enum symbolTypes {Type, Variable, Function};
    enum symbolKind {Simple, Array, Struct};

    string name;
    symbolTypes type;

    struct {

        struct {
            symbolKind kind;
            int size;
        } type;

        struct {
            bool init;
            string type;
            int relAddress;
            bool isConst;
        } variable;

        struct {
            int numOfArgs;
            string type;
            int localVarSize;
            vector<Symbol> arguments;
        } function;

    } attributes;
};

class SymbolTable {


    //queue used for types that are identifiers and need to be evaluated at the end
    //queue also used for identifiers of a class aka identifier.identifier where the second identifier need not
    //be known. It is read at end of parser compilation and then each item is checked to see whether if it is in
    //the symboltable, if not an error is thrown.

public:

    vector<Symbol> table;

    SymbolTable()= default;;

    void addSymbol(Symbol symbol);
    bool findSymbol(string name);
};

#endif //MYJC_SYMBOLTABLE_H
