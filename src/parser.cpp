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
    table = SymbolTable();

    if(token.getLexeme() == "class"){
        classDeclare();
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
        cerr << "Error occurred on line " << token.getLine() << " at or near '" << token.getLexeme() << "',";
        cerr << " expected " << msg << "." << endl;
        exit(2);
    }
    else if (errorType == "symbol"){
        cerr << "Error occurred on line " << token.getLine() << " at or near '" << token.getLexeme() << "', ";
        cerr << msg << "." << endl;
//        exit(2); //todo: switch from warnings once external classes are included
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
void Parser::operand(){

    token = lexer->getNextToken();
    if(token.getType() == Token::Integer){

    }
    else if(token.getType() == Token::Identifier) {

        if(!table.findSymbol(token.getLexeme())){
            error("symbol", "identifier not declared");
        }

        token = lexer->peekNextToken();
        if (token.getLexeme() == ".") {
            token = lexer->getNextToken();
            token = lexer->getNextToken();
            if (token.getType() == Token::Identifier) {
                //todo - check if this is necessary as specification suggests not
                //details: Using variables from another class from is permitted even when their declaration has not yet
                //been encountered by the compiler.
            }
            else {
                error("parser", "an identifier");
            }

            token = lexer->peekNextToken();
            if (token.getLexeme() == "[") {
                token = lexer->getNextToken();
                token = lexer->peekNextToken();
                if (isExpression()) {
                    expression();
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
                expression();
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
    }
    else if(token.getLexeme() == "("){
        token = lexer->peekNextToken();
        if(isExpression()) {
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
    }
    else if(token.getType() == Token::String){

    }
    else if(token.getLexeme() == "true"){

    }
    else if(token.getLexeme() == "false"){

    }
    else if(token.getLexeme() == "null"){

    }
    else if(token.getLexeme() == "this"){

    }
    else{
        error("parser", "an operand");
    }
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
void Parser::factor(){

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" || token.getLexeme() == "~"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
    }

    if(isOperand()){
        operand();
    }
    else{
        error("parser", "an operand");
    }
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
void Parser::term(){

    token = lexer->peekNextToken();
    if(isFactor()){
        factor();
    }
    else{
        error("parser", "a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "*" || token.getLexeme() == "/"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isFactor()){
            factor();
        }
        else{
            error("parser", "a factor");
        }
        token = lexer->peekNextToken();
    }

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
void Parser::arithmeticExpression(){

    token = lexer->peekNextToken();
    if(isTerm()){
        term();
    }
    else{
        error("parser", "a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "+" || token.getLexeme() == "-"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isTerm()){
            term();
        }
        else{
            error("parser", "a term");
        }
        token = lexer->peekNextToken();
    }

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
void Parser::relationalExpression(){

    token = lexer->peekNextToken();
    if(isArithmeticExpression()){
        arithmeticExpression();
    }
    else{
        error("parser", "an arithmetic expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "=" || token.getLexeme() == ">" || token.getLexeme() == "<"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();

        if(isArithmeticExpression()){
            arithmeticExpression();
        }
        else{
            error("parser", "an arithmetic expression");
        }
        token = lexer->peekNextToken();
    }
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
void Parser::expression(){

    token = lexer->peekNextToken();
    if(isRelationalExpression()){
        relationalExpression();
    }
    else{
        error("parser", "a relational expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "&" || token.getLexeme() == "|"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isRelationalExpression()){
            relationalExpression();
        }
        else{
            error("parser", "a relational expression");
        }
        token = lexer->peekNextToken();
    }

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
        expression();
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

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "."){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){

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

    expressionList();

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

/**
 * Handles if statement rule calls.
 * ifStatement -> if ( expression ) { {statement} } [else { {statement} }]
 */
void Parser::ifStatement(){

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
        statement();
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
    token = lexer->getNextToken();
    if(token.getLexeme() == "let"){

    }
    else{
        error("parser", "'let'");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        if(table.findSymbol(token.getLexeme())){

        }
        else{
            error("symbol", "not defined");
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
            expression();
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
        expression();
    }
    else{
        error("parser", "an expression");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

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

    token = lexer->getNextToken();
    if(token.getLexeme() == "var"){
        symbol.setType(Symbol::Variable);
    }
    else{
        error("parser", "'var'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        symbol.setVarType(token.getLexeme());

        if(token.getType() == Token::Identifier){
            int size = table.findSymbolSize(token.getLexeme());

            if(size != -1){
                symbol.setSize(size);
            }
            else{
                error("symbol","type not declared");
            }
        }
        else {
            symbol.setSize(token.getLexeme());
        }

    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        symbol.setName(token.getLexeme());
    }
    else{
        error("parser", "an identifier");
    }

    table.addSymbol(symbol); //add symbol to scope

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            symbol.setName(token.getLexeme());
        }
        else{
            error("parser", "an identifier");
        }

        table.addSymbol(symbol);

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
void Parser::statement(){

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
    }
    else{
        error("parser", "a statement");
    }
}

/**
 * Handles subroutine body rule calls.
 * subroutineBody -> { {statement} }
 */
void Parser::subroutineBody(){

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

/**
 * Handles param list rule calls.
 * paramList -> type identifier {, type identifier} | ε
 */
vector<Symbol> Parser::paramList(){

    vector<Symbol> param;
    Symbol symbol;

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        symbol.setVarType(token.getLexeme());
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        symbol.setName(token.getLexeme());
    }

    param.push_back(symbol);

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
            type();
            symbol.setVarType(token.getLexeme());
        }
        else {
            error("parser", "a type");
        }

        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            symbol.setName(token.getLexeme());
        }
        else{
            error("parser", "an identifier");
        }

        param.push_back(symbol);

        token = lexer->peekNextToken();
    }

    return param;
}

/**
 * Handles subroutine declare rule calls.
 * subroutineDeclar -> (constructor | function | method) (type|void) identifier (paramList) subroutineBody
 */
void Parser::subroutineDeclare() {

    Symbol symbol;

    token = lexer->getNextToken();
    if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        symbol.setType(Symbol::Function);
    }
    else{
        error("parser", "a subroutine declaration");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        symbol.setRetType(token.getLexeme());
    }
    else if(token.getLexeme() == "void"){
        token = lexer->getNextToken();
    }
    else{
        error("parser", "type or 'void'");
    }

    token = lexer->getNextToken();
    if(token.getType() ==  Token::Identifier){
        symbol.setName(token.getLexeme());
    }
    else{
        error("parser", "an identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("parser", "'('");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        symbol.setArgs(paramList());
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("parser", "')'");
    }

    table.addScope(); //add new scope
    Symbol local = symbol;
    local.setName("this");
    table.addSymbol(local);

    token = lexer->peekNextToken();
    if(token.getLexeme() == "{"){
        subroutineBody();
    }
    else{
        error("parser", "'{'");
    }

    symbol.setLocVarSize(table.getSize());
    table.delScope();
    table.addSymbol(symbol); //todo: check if required
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

    Symbol symbol;
    symbol.setType(Symbol::Variable);

    token = lexer->getNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){

    }
    else{
        error("parser", "'static' or 'field'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
        symbol.setVarType(token.getLexeme());
    }
    else{
        error("parser", "a var type or identifier");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        symbol.setName(token.getLexeme());
    }
    else{
        error("parser", "an identifier");
    }

    table.addSymbol(symbol); //add symbol to scope

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){
            symbol.setName(token.getLexeme());
            table.addSymbol(symbol); //add symbol to scope
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

    Symbol symbol;

    table.addSymbol(symbol);

    token = lexer->getNextToken();
    if(token.getLexeme() == "class"){
        symbol.setType(Symbol::Type);
        symbol.setKind(Symbol::Object);
    }
    else{
        error("parser", "class");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        if(!table.findSymbol(token.getLexeme())){
            symbol.setName(token.getLexeme());
        }
        else{
            error("symbol", "class already declared");
        }
    }
    else{
        error("parser", "an Identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){
        table.addScope();
    }
    else{
        error("parser", "{");
    }

    table.addSymbol(symbol); //add class to table

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

    auto temp = table.getSize(); //set size of class to size of table
    table.delScope(); //destroy local scope
    table.editSymbol(symbol.getName())->setSize(temp); //set the size of the class

}

