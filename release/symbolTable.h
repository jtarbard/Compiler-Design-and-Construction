//
// Created by sc18jt on 25/03/2020.
//

#ifndef MYJC_SYMBOLTABLE_H
#define MYJC_SYMBOLTABLE_H

#include <string>
#include <utility>
#include <vector>
#include <list>

using namespace std;

class SymbolTable;
class Table;

class Symbol {

public:
    enum symbolKind {Field, Static, Local, Argument, Simple, Array, Struct, Function};

    void setName(string pName){name = std::move(pName);}
    void setType(string pType){type = std::move(pType);}
    void setKind(symbolKind pKind){kind = pKind;}
    void setInit(bool pInit){initialised = pInit;}
    void setRelAdd(int pRelAdd){relativeAddress = pRelAdd;}
    void setArgs(vector<Symbol> args){arguments = std::move(args);};

    string getName(){return name;}
    string getType(){return type;}
    symbolKind getKind(){return kind;}
    bool getInit(){return initialised;}
    int getRelAdd(){return relativeAddress;}
    vector<Symbol>* getArgs(){return &arguments;}

private:

    string name;
    string type;
    symbolKind kind;
    int relativeAddress;
    vector<Symbol> arguments;
    bool initialised = false;


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

    virtual Symbol* editSymbol(string name);

    virtual bool findSymbol(string name);


};

class SymbolTable : public Table {
public:
    SymbolTable();

    Table global;
    Table local;

    bool findSymbol(string name);
    void display(string file);

    Symbol *editSymbol(string name);
};

#endif //MYJC_SYMBOLTABLE_H
