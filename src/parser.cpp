//
// Created by sc18jt on 04/03/2020.
//

#include "parser.h"

/**
 * Parser Constructor.
 */
Parser::Parser(Lexer *parLexer) {
    lexer = parLexer;
    Token token = lexer->peekNextToken();
    if(token.getLexeme() == "class"){
        classDeclare();
    }
    else{
        error();
    }
}

void Parser::error() {
    cerr << "Error occurred on line " << token.getLine() << " at or near '" << token.getLexeme() << "'.";
    exit(2);
}

void Parser::error(char* msg) {
    cerr << "Error occurred on line " << token.getLine() << " at or near '" << token.getLexeme() << "',";
    cerr << " expected " << msg << ".";
    exit(2);
}

//TODO: check use of checks on expressions and all below for errors due to not including (expression)
//as seen in relational expression

void Parser::operand(){
    cout << "in operand\n";

    token = lexer->getNextToken();
    if(token.getType() == Token::Integer){

    }
    else if(token.getType() == Token::Identifier){
        token = lexer->peekNextToken();
        if(token.getLexeme() == "."){
            token = lexer->getNextToken();
            token = lexer->getNextToken();
            if(token.getType() == Token::Identifier){

            }
            else{
                error();
            }
        }
    }
    else if(token.getLexeme() == "["){
        token = lexer->peekNextToken();
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            expression();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            expression();
        }
        else{
            error();
        }
    }
    else if(token.getLexeme() == "("){
        token = lexer->peekNextToken();
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            expressionList();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            expressionList();
        }
        else{
            error();
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
        error();
    }
}

/**
 *
 * factor -> ( - | ~ | ε ) operand
 */
void Parser::factor(){
    cout << "in factor \n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "-" || token.getLexeme() == "~"){

    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        operand();
    }
    else{
        error();
    }
}

/**
 * term -> factor { ( * | / ) factor }
 */
void Parser::term(){
    cout << "term\n";

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        term();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        term();
    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "*" || token.getLexeme() == "/"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            factor();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            factor();
        }
        else{
            error();
        }
    }

}

/**
 *
 * ArithmeticExpression  term { ( + | - ) term }
 */
void Parser::arithmeticExpression(){
    cout << "arithmetic expression\n";

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        term();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        term();
    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "+" || token.getLexeme() == "-"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            term();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            term();
        }
        else{
            error();
        }
    }

}

/**
 *
 * relationalExpression -> ArithmeticExpression { ( = | > | < ) ArithmeticExpression }
 */
void Parser::relationalExpression(){
    cout << "relation expression\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        arithmeticExpression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        arithmeticExpression();
    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "{" || token.getLexeme() == ">" || token.getLexeme() == "<"){
        token = lexer->getNextToken();
        token = lexer->getNextToken();

        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            arithmeticExpression();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            arithmeticExpression();
        }
        else{
            error();
        }
    }
}

/**
 *
 * expression -> relationalExpression { ( & | | ) relationalExpression }
 */
void Parser::expression(){
    cout << "expression\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        relationalExpression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        relationalExpression();
    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "&" || token.getLexeme() == "|"){
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            relationalExpression();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            relationalExpression();
        }
        else{
            error();
        }
    }

}

/**
 *
 * returnStatemnt -> return [ expression ] ;
 */
void Parser::returnStatement(){
    cout << "return statement\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "return"){

    }
    else{
        error("'return'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        expression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        expression();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("';'");
    }
}

/**
 * expressionList -> expression { , expression } | ε
 */
void Parser::expressionList(){
    cout << "in expression list\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        expression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        expression();
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            expression();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            expression();
        }
        else{
            error();
        }
        token = lexer->peekNextToken();
    }
}

/**
 *
 * subroutineCall -> identifier [ . identifier ] ( expressionList )
 */
void Parser::subroutineCall(){
    cout << "subroutine call\n";

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
    }
    else{
        error("an identifier");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "."){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){

        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        expressionList();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        expressionList();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("')'");
    }
}

/**
 *
 * doStatement -> do subroutineCall ;
 */
void Parser::doStatement(){
    cout << "do statement\n";

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){
        subroutineCall();
    }
    else{
        error("an identifier");
    }
}

/**
 *
 * whileStatement -> while ( expression ) { {statement} }
 */
void Parser::whileStatement(){
    cout << "while statement\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "while"){

    }
    else{
        error("'while'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        expression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        expression();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("')'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("'{'");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return"){
        statement();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("'}'");
    }
}

/**
 *
 * ifStatement -> if ( expression ) { {statement} } [else { {statement} }]
 */
void Parser::ifStatement(){
    cout << "if statement\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "if"){

    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        term();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        term();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("')'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("'{'");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return"){
        statement();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("'}'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "else"){
        token = lexer->getNextToken();
        if(token.getLexeme() == "{"){

        }
        else{
            error("'{'");
        }

        token = lexer->peekNextToken();
        while(token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return"){
            statement();
            token = lexer->peekNextToken();
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == "}"){

        }
        else{
            error("'}'");
        }

    }

}

/**
 *
 * letStatemnt -> let identifier [ [ expression ] ] = expression ;
 */
void Parser::letStatement(){
    cout << "let statement\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "let"){

    }
    else{
        error("'let'");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error("an identifier");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "["){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        //TODO: check logic
        if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
            expression();
        }
        else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
            expression();
        }
        else{
            error();
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == "]"){

        }
        else{
            error();
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "="){

    }
    else{
        error("'='");
    }

    //TODO: check logic
    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" ||token.getLexeme() == "~"){
        expression();
    }
    else if(token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" || token.getLexeme() == "null" || token.getLexeme() == "this") {
        expression();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("';'");
    }

}

/**
 *
 * varDeclarStatement -> var type identifier { , identifier } ;
 */
void Parser::varDeclareStatement(){
    cout << "var declare statement\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "var"){

    }
    else{
        error("'var'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error("an identifier");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){

        }
        else{
            error();
        }
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error();
    }
}

/**
 *
 * statement -> varDeclarStatement | letStatemnt | ifStatement | whileStatement | doStatement | returnStatemnt
 */
void Parser::statement(){
    cout << "in statement\n";

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
        error();
    }
}

/**
 *
 * subroutineBody -> { {statement} }
 */
void Parser::subroutineBody(){
    cout << "In subroutine body\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("'{'");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return"){
        statement();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("'}'");
    }
}

/**
 *
 * paramList -> type identifier {, type identifier} | ε
 */
void Parser::paramList(){
    cout << "In param list\n";
    token = lexer->getNextToken();

    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }
    else {
        error("a type");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error("an identifier");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->getNextToken();
        if(token.getType() == Token::Identifier){

        }
        else{
            error("an identifier");
        }
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("';");
    }
}

/**
 *
 * subroutineDeclar -> (constructor | function | method) (type|void) identifier (paramList) subroutineBody
 */
void Parser::subroutineDeclare() {
    cout << "in subroutine declare\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){

    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }
    else if(token.getLexeme() == "void"){
        token = lexer->getNextToken();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getType() ==  Token::Identifier){

    }
    else{
        error("an identifier.");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("(");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        paramList();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error(")");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "{"){
        subroutineBody();
    }
    else{
        error();
    }
}

/**
 *
 * type -> int | char | boolean | identifier
 */
void Parser::type(){
    cout << "in type\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){

    }
    else{
        error();
    }
}

/**
 *
 * classVarDeclar -> (static | field) type identifier {, identifier} ;
 */
void Parser::memberDeclare() {
    cout << "in member declare\n";
    token = lexer->peekNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){
        classVarDeclare();
    }
    else if(token.getLexeme() == "const" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        subroutineDeclare();
    }
    else{
        error();
    }
}

/**
 *
 * memberDeclar -> classVarDeclar | subroutineDeclar
 */
void Parser::classVarDeclare() {
    cout << "in class var declare\n";
    token = lexer->getNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){

    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }
    else{
        error();
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error();
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(token.getType() == Token::Identifier){
            token = lexer->getNextToken();
        }
        else{
            error();
        }
        token = lexer->getNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error();
    }
}

/**
 *
 * classDeclar -> class identifier { {memberDeclar} }
 */
void Parser::classDeclare() {
    cout << "in Class declare\n";
    token = lexer->getNextToken();
    if(token.getLexeme() == "class"){

    }
    else{
        error("class");
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }
    else{
        error("an Identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("{");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "static" || token.getLexeme() == "field" || token.getLexeme() == "const" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        memberDeclare();
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "}"){

    }
    else{
        error("}");
    }

}

