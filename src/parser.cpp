//
// Created by sc18jt on 04/03/2020.
//

#include "parser.h"
#include "symbolTable.h"

/**
 * Initalises the recursive decent by checking for a class declariton
 * and calling class declare.
 */
Parser::Parser(Lexer *parLexer) {
    lexer = parLexer;
    token = lexer->peekNextToken();

    if(token.getLexeme() == "class"){
        classDeclare();
        cout << lexer->getFileName() << endl;
        symbolTable.display();
    }
    else{
        error("parser", "a class declaration");
    }
}

/**
 * Returns a cerr message informing the user of the line
 * the error occured on, the lexeme at the point of error
 * and what the parser expected at that point.
 * @param msg   a string containing the expected character/type/rule
 */
void Parser::error(string errorType,string msg) {
    if (errorType == "parser") {
        cerr << lexer->getFileName() << "::" << token.getLine() << " Error: at or near '" << token.getLexeme() << "',"
        << " expected " << msg << ".\n" << endl;
        exit(2);
    }
    else if (errorType == "symbol"){
        cerr << lexer->getFileName() << "::" << token.getLine() << " Warning: at or near '" << token.getLexeme()
        << "', " << msg << ".\n" << endl;
    }
    else if (errorType == "custom"){
        cerr << lexer->getFileName() << "::" << token.getLine() << " Warning: " << msg << ".\n" << endl;;
    }
}

void Parser::setSymbolType(Symbol* symbol){
    //set symbol type todo: does this need to throw an error
    symbol->setType(token.getLexeme());
}

void Parser::setSymbolName(Symbol* symbol, Table table){
    //check for duplicate declaration
    if(!table.findSymbol(token.getLexeme())){
        //add symbol name and add symbol to global scope
        symbol->setName(token.getLexeme());
    }
    else{
        error("symbol", "identifier is already declared");
    }
}

void Parser::typeChecker(string t1, string t2){
    if(t1 != t2){
        if(t1 == "int" || t1 == "char" || t1 == "boolean"){
            if(t2 == "int" || t2 == "char" || t2 == "boolean"){
                error("symbol", "expression types "+t1+" and "+t2+" do not match");
            }
        }
    }
}


void Parser::typeChecker(string t1){
    if(t1 == "char" || t1 == "boolean"){
        error("symbol", "array index is not of required type int");
    }
}

/**
 * Checks if token lexeme/type matches operand rule.
 * @return  a bool containing rule match result
 */
bool Parser::isOperand(){
    return token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" ||
           token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" ||
           token.getLexeme() == "null" || token.getLexeme() == "this";
}

/**
 * Handles operand rule calls.
 * operand  integerConstant | identifier [.identifier ] [ [ expression ] | (expressionList ) ] | (expression) | stringLiteral | true | false | null | this
 */
string Parser::operand(){

    string symbolName;
    string type;

    token = lexer->getNextToken();
    if(token.getType() == Token::Integer){
        type = "int";
    }
    else if(token.getType() == Token::Identifier) {

        if(!(symbolTable.findSymbol(token.getLexeme())) && lexer->peekNextToken().getLexeme() != "."){
            error("symbol", "identifier is not declared");
        }
        else{
            symbolName = token.getLexeme();
        }

        if(symbolTable.findSymbol(token.getLexeme())){
            type = symbolTable.editSymbol(token.getLexeme())->getType();
        }
        else{
            type = token.getLexeme();
        }

        token = lexer->peekNextToken();
        if (token.getLexeme() == ".") {
            token = lexer->getNextToken();
            token = lexer->getNextToken();
            if (token.getType() == Token::Identifier) {
                if(symbolTable.findSymbol(token.getLexeme())){
                    type = symbolTable.editSymbol(token.getLexeme())->getType();
                }
                else{
                    type = token.getLexeme();
                }
            }
            else {
                error("parser", "an identifier");
            }

            token = lexer->peekNextToken();
            if (token.getLexeme() == "[") {
                token = lexer->getNextToken();
                token = lexer->peekNextToken();
                if (isExpression()) {
                    typeChecker(expression());
                } else {
                    error("parser", "an expression");
                }

                token = lexer->getNextToken();
                if (token.getLexeme() == "]") {

                } else {
                    error("parser", "']'");
                }
            }
            else if (token.getLexeme() == "(") {
                token = lexer->getNextToken();
                token = lexer->peekNextToken();
                expressionList();

                token = lexer->getNextToken();
                if (token.getLexeme() == ")") {

                } else {
                    error("parser", "')'");
                }
            }
        }
        else if (token.getLexeme() == "[") {

            token = lexer->getNextToken();
            token = lexer->peekNextToken();
            if (isExpression()) {
                typeChecker(expression());
            }
            else {
                error("parser", "an expression");
            }

            token = lexer->getNextToken();
            if (token.getLexeme() == "]") {

            }
            else {
                error("parser", "']'");
            }
        }
        else if (token.getLexeme() == "(") {
            token = lexer->getNextToken();
            token = lexer->peekNextToken();
            expressionList();

            token = lexer->getNextToken();
            if (token.getLexeme() == ")") {

            } else {
                error("parser", "')'");
            }
        }
        else{
            if(symbolTable.findSymbol(symbolName)){
                if(!symbolTable.editSymbol(symbolName)->getInit()){
                    error("custom", "'"+symbolName+"' is not initialised");
                }
            }
        }
    }
    else if(token.getLexeme() == "("){
        token = lexer->peekNextToken();
        if(isExpression()) {
            type = expression();
        }
        else{
            error("parser", "an expression");
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == ")"){

        }
        else{
            error("parser", "')'");
        }
    }
    else if(token.getType() == Token::String){
        type = "char";
    }
    else if(token.getLexeme() == "true"){
        type = "boolean";
    }
    else if(token.getLexeme() == "false"){
        type = "boolean";
    }
    else if(token.getLexeme() == "null"){
        type = "point";
    }
    else if(token.getLexeme() == "this"){
        if(symbolTable.findSymbol("this")){
            type = symbolTable.editSymbol("this")->getType();
        }
        else{
            type = "this";
        }
    }
    else{
        error("parser", "an operand");
    }

    return type;
}

/**
 * Checks if token lexeme/type matches factor rule.
 * @return  a bool containing rule match result
 */
bool Parser::isFactor(){
    return token.getLexeme() == "-" || token.getLexeme() == "~" || isOperand();
}

/**
 * Handles factor rule calls.
 * factor -> ( - | ~ | ε ) operand
 */
string Parser::factor(){

    string type;

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" || token.getLexeme() == "~"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
    }

    if(isOperand()){
        type = operand();
    }
    else{
        error("parser", "an operand");
    }

    return type;
}

/**
 * Checks if token lexeme/type matches term rule.
 * @return  a bool containing rule match result
 */
bool Parser::isTerm(){
    return isFactor();
}

/**
 * Handles term rule calls.
 * term -> factor { ( * | / ) factor }
 */
string Parser::term(){

    string type;

    token = lexer->peekNextToken();
    if(isFactor()){
        type = factor();
    }
    else{
        error("parser", "a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "*" || token.getLexeme() == "/"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isFactor()) {
            typeChecker(type, factor());
        }
        else{
            error("parser", "a factor");
        }
        token = lexer->peekNextToken();
    }

    return type;

}

/**
 * Checks if token lexeme/type matches arithmetic
 * expression rule.
 * @return  a bool containing rule match result
 */
bool Parser::isArithmeticExpression(){
    return isTerm();
}

/**
 * Handles arithmetic expression rule calls.
 * ArithmeticExpression  term { ( + | - ) term }
 */
string Parser::arithmeticExpression(){

    string type;

    token = lexer->peekNextToken();
    if(isTerm()){
        type = term();
    }
    else{
        error("parser", "a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "+" || token.getLexeme() == "-"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isTerm()){
            typeChecker(type, term());
        }
        else{
            error("parser", "a term");
        }
        token = lexer->peekNextToken();
    }

    return type;

}

/**
 * Checks if token lexeme/type matches relation
 * expression rule.
 * @return  a bool containing rule match result
 */
bool Parser::isRelationalExpression(){
    return isArithmeticExpression();
}

/**
 * Handles relational expression rule calls.
 * relationalExpression -> ArithmeticExpression { ( = | > | < ) ArithmeticExpression }
 */
string Parser::relationalExpression(){

    string type;

    token = lexer->peekNextToken();
    if(isArithmeticExpression()){
        type = arithmeticExpression();
    }
    else{
        error("parser", "an arithmetic expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "=" || token.getLexeme() == ">" || token.getLexeme() == "<"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();

        if(isArithmeticExpression()){
            typeChecker(type, arithmeticExpression());
        }
        else{
            error("parser", "an arithmetic expression");
        }
        token = lexer->peekNextToken();
    }

    return type;
}

/**
 * Checks if token lexeme/type matches expression rule.
 * @return  a bool containing rule match result
 */
bool Parser::isExpression(){
    return isRelationalExpression();
}

/**
 * Handles expression rule calls.
 * expression -> relationalExpression { ( & | | ) relationalExpression }
 */
string Parser::expression(){

    string type;

    token = lexer->peekNextToken();
    if(isRelationalExpression()){
        type = relationalExpression();
    }
    else{
        error("parser", "a relational expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "&" || token.getLexeme() == "|"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isRelationalExpression()){
            typeChecker(type, relationalExpression());
        }
        else{
            error("parser", "a relational expression");
        }
        token = lexer->peekNextToken();
    }

    return type;
}

/**
 * Handles return statement rule calls.
 * returnStatemnt -> return [ expression ] ;
 */
void Parser::returnStatement(){

    token = lexer->getNextToken();
    if(token.getLexeme() == "return"){

    }
    else{
        error("parser", "'return'");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
        if(symbolTable.global.findSymbol(symbolTable.local.editSymbol("this")->getType())) {
            typeChecker(symbolTable.global.editSymbol(symbolTable.local.editSymbol("this")->getType())->getType(),
                    expression());
        }
        else{
            expression();
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("parser", "';'");
    }
}

/**
 * Handles expression list rule calls.
 * expressionList -> expression { , expression } | ε
 */
void Parser::expressionList(){

    token = lexer->peekNextToken();
    if(isExpression()){
        expression();
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isExpression()){
            expression();
        }
        else{
            error("parser", "an expression");
        }
        token = lexer->peekNextToken();
    }
}

/**
 * Handles expression list rule calls.
 * expressionList -> expression { , expression } | ε
 */
void Parser::expressionList(vector<Symbol> args){

    int argCt = 1;
    int limit = args.size();

    token = lexer->peekNextToken();
    if(isExpression()){
        typeChecker(args.at(argCt).getType(), expression());
        argCt++;
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isExpression()){
            if(argCt < limit) {
                typeChecker(args.at(argCt).getType(), expression());
                argCt++;
            }
            else{
                expression();
                argCt++;
            }
        }
        else{
            error("parser", "an expression");
        }
        token = lexer->peekNextToken();
    }

    if(argCt > limit){
        error("symbol", "too many arguments provided");
    }
    else if(argCt < limit){
        error("symbol", "too few arguments provided");
    }
}

/**
 * Checks if token lexeme/type matches subroutine
 * call rule.
 * @return  a bool containing rule match result
 */
bool Parser::isSubroutineCall(){
    return token.getType() == Token::Identifier;
}

/**
 *  Handles subroutine call rule calls.
 *  subroutineCall -> identifier [ . identifier ] ( expressionList )
 */
void Parser::subroutineCall(){

    string subroutine = "";

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        if(symbolTable.findSymbol(token.getLexeme())){
            subroutine = token.getLexeme();
        }
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "."){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            if(symbolTable.findSymbol(token.getLexeme())){
                subroutine = token.getLexeme();
            }
        }
        else{
            error("parser", "an identifier");
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("parser", "'('");
    }

    if(subroutine == "") {
        expressionList();
    }
    else {
        if(symbolTable.findSymbol(subroutine)) {
            expressionList(symbolTable.editSymbol(subroutine)->getArgs());
        }
        else{
            expressionList();
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("parser", "')'");
    }
}

/**
 * Handles do statement rule calls.
 * doStatement -> do subroutineCall ;
 */
void Parser::doStatement(){

    token = lexer->getNextToken();
    token = lexer->peekNextToken();
    if(isSubroutineCall()){
        subroutineCall();
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("parser", "';'");
    }
}

/**
 *  Handles while statement rule calls.
 * whileStatement -> while ( expression ) { {statement} }
 */
void Parser::whileStatement(){

    int isGoodPath = 0;

    token = lexer->getNextToken();
    if(token.getLexeme() == "while"){

    }
    else{
        error("parser", "'while'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("parser", "'('");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
        expression();
    }
    else{
        error("parser", "an expression");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("parser", "')'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("parser", "'{'");
    }

    token = lexer->peekNextToken();
    while(isStatement()){
        if(isGoodPath == 1) {
            error("symbol", "code be reachable");
        }
        isGoodPath = statement();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("parser", "'}'");
    }
}

/**
 * Handles if statement rule calls.
 * ifStatement -> if ( expression ) { {statement} } [else { {statement} }]
 */
void Parser::ifStatement(){

    int isGoodPath = 0;

    token = lexer->getNextToken();
    if(token.getLexeme() == "if"){

    }
    else{
        error("parser", "'if'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("parser", "'('");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
        expression();
    }
    else{
        error("parser", "an expression");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("parser", "')'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("parser", "'{'");
    }

    token = lexer->peekNextToken();
    while(isStatement()){
        if(isGoodPath == 1) {
            error("symbol", "code is not reachable");
        }
        isGoodPath = statement();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("parser", "'}'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "else"){
        token = lexer->getNextToken();
        if(token.getLexeme() == "{"){

        }
        else{
            error("parser", "'{'");
        }

        token = lexer->peekNextToken();
        while(isStatement()){
            statement();
            token = lexer->peekNextToken();
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == "}"){

        }
        else{
            error("parser", "'}'");
        }

    }

}

/**
 * Handles let statement rule calls.
 * letStatemnt -> let identifier [ [ expression ] ] = expression ;
 */
void Parser::letStatement(){

    string symbolName;

    token = lexer->getNextToken();
    if(token.getLexeme() == "let"){

    }
    else{
        error("parser", "'let'");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        //check for declaration in all scopes
        if(symbolTable.findSymbol(token.getLexeme())){
            symbolName = token.getLexeme();
        }
        else{
            error("symbol", "identifier is not declared");
        }
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "["){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();

        if(isExpression()){
            typeChecker(expression());
        }
        else{
            error("parser", "an expression");
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == "]"){

        }
        else{
            error("parser", "']");
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "="){

    }
    else{
        error("parser", "'='");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
        if(symbolTable.findSymbol(symbolName)) {
            typeChecker(symbolTable.editSymbol(symbolName)->getType(), expression());
        }
        else{
            expression();
        }
    }
    else{
        error("parser", "an expression");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){
        if(symbolTable.findSymbol(symbolName)) {
            symbolTable.editSymbol(symbolName)->setInit(true);
        }
    }
    else{
        error("parser", "';'");
    }

}
/**
 * Handles var decalre statement rule calls.
 * varDeclarStatement -> var type identifier { , identifier } ;
 */
void Parser::varDeclareStatement(){

    Symbol symbol;
    symbol.setKind(Symbol::Local);

    token = lexer->getNextToken();
    if(token.getLexeme() == "var"){

    }
    else{
        error("parser", "'var'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        setSymbolType(&symbol); //set symbol type
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        setSymbolName(&symbol, symbolTable.local); //set symbol name if not duplicate
        symbolTable.local.addSymbol(symbol);
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            setSymbolName(&symbol, symbolTable.local); //set symbol name if not duplicate
            symbolTable.local.addSymbol(symbol);
        }
        else{
            error("parser", "an identifier");
        }
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("parser", "';'");
    }
}

/**
 * Checks if token lexeme/type matches statement rule.
 * @return  a bool containing rule match result
 */
bool Parser::isStatement(){
    return token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return";
}

/**
 * Handles statement rule calls.
 * statement -> varDeclarStatement | letStatemnt | ifStatement | whileStatement | doStatement | returnStatemnt
 */
int Parser::statement(){

    token = lexer->peekNextToken();
    if(token.getLexeme() == "var"){
        varDeclareStatement();
    }
    else if(token.getLexeme() == "let"){
        letStatement();
    }
    else if(token.getLexeme() == "if"){
        ifStatement();
    }
    else if(token.getLexeme() == "while"){
        whileStatement();
    }
    else if(token.getLexeme() == "do"){
        doStatement();
    }
    else if(token.getLexeme() == "return"){
        returnStatement();
        return 1;
    }
    else{
        error("parser", "a statement");
    }

    return false;
}

/**
 * Handles subroutine body rule calls.
 * subroutineBody -> { {statement} }
 */
void Parser::subroutineBody(){

    int lastPath = 0;

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("parser", "'{'");
    }

    token = lexer->peekNextToken();
    while(isStatement()){
        if(lastPath == 1){
            error("custom", "code may be unreachable");
        }
        lastPath = statement();
        token = lexer->peekNextToken();

    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("parser", "'}'");
    }

    if(lastPath == 0){
        error("custom", "not all function paths return a value");
    }
}

/**
 * Handles param list rule calls.
 * paramList -> type identifier {, type identifier} | ε
 */
void Parser::paramList(){

    Symbol symbol;
    symbol.setKind(Symbol::Argument);
    symbol.setInit(true);

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        symbol.setType(token.getLexeme());
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        if(!symbolTable.local.findSymbol(token.getLexeme())){
            symbol.setName(token.getLexeme());
        }
        else {
            error("symbol", "identifier is already declared");
        }
    }

    symbolTable.local.addSymbol(symbol);

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
            type();
        }
        else {
            error("parser", "a type");
        }

        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            if(!symbolTable.local.findSymbol(token.getLexeme())){
                symbol.setName(token.getLexeme());
                symbolTable.local.addSymbol(symbol);
            }
            else {
                error("symbol", "identifier is already declared");
            }
        }
        else{
            error("parser", "an identifier");
        }
        token = lexer->peekNextToken();
    }
}

/**
 * Handles subroutine declare rule calls.
 * subroutineDeclar -> (constructor | function | method) (type|void) identifier (paramList) subroutineBody
 */
void Parser::subroutineDeclare() {

    if(symbolTable.local.table.size() > 0){
        symbolTable.local.table.clear();
    }

    //create symbol for new subroutine
    Symbol symbol;
    symbol.setKind(Symbol::Function);
    vector<Symbol> table;

    token = lexer->getNextToken();
    if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){

    }
    else{
        error("parser", "a subroutine declaration");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        setSymbolType(&symbol); //set the symbols type
    }
    else if(token.getLexeme() == "void"){
        token = lexer->getNextToken();
    }
    else{
        error("parser", "type or 'void'");
    }

    token = lexer->getNextToken();
    if(token.getType() ==  Token::Identifier){
        setSymbolName(&symbol, symbolTable.global); //set symbol name if not duplicate
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){
        //add this variable as first argument
        Symbol _this;
        _this.setName("this");
        _this.setType(symbol.getName());
        _this.setKind(Symbol::Argument);
        symbolTable.local.addSymbol(_this);
    }
    else{
        error("parser", "'('");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        paramList();
        for(auto s : symbolTable.local.table){
            if(s.getKind() == Symbol::Argument){
                table.push_back(s);
            }
        }
    }

    symbol.setArgs(table);
    symbolTable.global.addSymbol(symbol); //add symbol to class scope

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("parser", "')'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "{"){
        subroutineBody();
    }
    else{
        error("parser", "'{'");
    }
}

/**
 * Handles type rule calls.
 * type -> int | char | boolean | identifier
 */
void Parser::type(){

    token = lexer->getNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){

    }
    else{
        error("parser", "a var type or identifier");
    }
}

/**
 * Handles class var declare rule calls.
 * classVarDeclar -> (static | field) type identifier {, identifier} ;
 */
void Parser::memberDeclare() {

    token = lexer->peekNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){
        classVarDeclare();
    }
    else if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        subroutineDeclare();
    }
    else{
        error("parser", "a class declaration or subroutine declaration");
    }
}

/**
 * Handles member declare rule calls.
 * memberDeclar -> classVarDeclar | subroutineDeclar
 */
void Parser::classVarDeclare() {

    //create symbol for class variables
    Symbol symbol;

    token = lexer->getNextToken();
    if(token.getLexeme() == "static"){
        //set symbol kind static
        symbol.setKind(Symbol::Static);
    }
    else if(token.getLexeme() == "field"){
        //set symbol kind static
        symbol.setKind(Symbol::Field);
    }
    else{
        error("parser", "'static' or 'field'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        setSymbolType(&symbol); //set the symbols type
    }
    else{
        error("parser", "a var type or identifier");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        setSymbolName(&symbol, symbolTable.global); //set symbol name if not duplicate
    }
    else{
        error("parser", "an identifier");
    }

    //add symbol to global scope
    symbolTable.global.addSymbol(symbol);

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            setSymbolName(&symbol, symbolTable.global); //set symbol name if not duplicate
            symbolTable.global.addSymbol(symbol);
        }
        else{
            error("parser", "an identifier");
        }
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("parser", "';'");
    }
}

/**
 * Handles class decalre rule calls.
 * classDeclar -> class identifier { {memberDeclar} }
 */
void Parser::classDeclare() {

    if(symbolTable.global.table.size() > 0){
        symbolTable.global.table.clear();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "class"){

    }
    else{
        error("parser", "class");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error("parser", "an Identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("parser", "{");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "static" || token.getLexeme() == "field" || token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        memberDeclare();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("parser", "}");
    }

}

