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
        error("a class declaration");
    }
}

void Parser::error(string msg) {
    cerr << "Error occurred on line " << token.getLine() << " at or near '" << token.getLexeme() << "',";
    cerr << " expected " << msg << "." << endl;
    exit(2);
}

//TODO: check use of checks on expressions and all below for errors due to not including (expression)
//as seen in relational expression


bool Parser::isOperand(){
    return token.getType() == Token::Integer || token.getType() == Token::Identifier || token.getLexeme() == "(" ||
           token.getType() == Token::String || token.getLexeme() == "true" || token.getLexeme() == "false" ||
           token.getLexeme() == "null" || token.getLexeme() == "this";
}

void Parser::operand(){
    cout << "in operand - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getType() == Token::Integer){

    }
    else if(token.getType() == Token::Identifier) {

        token = lexer->peekNextToken();
        if (token.getLexeme() == ".") {
            token = lexer->getNextToken();
            token = lexer->getNextToken();
            if (token.getType() == Token::Identifier) {

            }
            else {
                error("an identifier");
            }

            token = lexer->peekNextToken();
            if (token.getLexeme() == "[") {
                token = lexer->getNextToken();
                token = lexer->peekNextToken();
                if (isExpression()) {
                    expression();
                } else {
                    error("an expression");
                }

                token = lexer->getNextToken();
                if (token.getLexeme() == "]") {

                } else {
                    error("']'");
                }
            }
            else if (token.getLexeme() == "(") {
                token = lexer->getNextToken();
                token = lexer->peekNextToken();
                expressionList(); //expresionList

                token = lexer->getNextToken();
                if (token.getLexeme() == ")") {

                } else {
                    error("')'");
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
                error("an expression");
            }

            token = lexer->getNextToken();
            if (token.getLexeme() == "]") {

            }
            else {
                error("']'");
            }
        }
        else if (token.getLexeme() == "(") {
            token = lexer->getNextToken();
            token = lexer->peekNextToken();
            expressionList(); //expressionList

            token = lexer->getNextToken();
            if (token.getLexeme() == ")") {

            } else {
                error("')'");
            }
        }
    }
    else if(token.getLexeme() == "("){
        token = lexer->peekNextToken();
        if(isExpression()) {
            expression();
        }
        else{
            error("an expression");
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == ")"){

        }
        else{
            error("')'");
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
        error("an operand");
    }
}

bool Parser::isFactor(){
    return token.getLexeme() == "-" || token.getLexeme() == "~" || isOperand();
}

/**
 *
 * factor -> ( - | ~ | ε ) operand
 */
void Parser::factor(){
    cout << "in factor  - " << token.getLexeme();
    cout << ", peak: expression - " << lexer->peekNextToken().getLexeme() << "\n";


    token = lexer->peekNextToken();
    if(token.getLexeme() == "-" || token.getLexeme() == "~"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
    }

    if(isOperand()){
        operand();
    }
    else{
        error("an operand");
    }
}

bool Parser::isTerm(){
    return isFactor();
}

/**
 * term -> factor { ( * | / ) factor }
 */
void Parser::term(){
    cout << "term - " << token.getLexeme();
    cout << ", peak: term - " << lexer->peekNextToken().getLexeme() << "\n";

    token = lexer->peekNextToken();
    if(isFactor()){
        factor();
    }
    else{
        error("a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "*" || token.getLexeme() == "/"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isFactor()){
            factor();
        }
        else{
            error("a factor");
        }
        token = lexer->peekNextToken();
    }

}

bool Parser::isArithmeticExpression(){
    return isTerm();
}

/**
 *
 * ArithmeticExpression  term { ( + | - ) term }
 */
void Parser::arithmeticExpression(){
    cout << "arithmetic expression - " << token.getLexeme();
    cout << ", peak: arithmetic expression - " << lexer->peekNextToken().getLexeme() << "\n";

    token = lexer->peekNextToken();
    if(isTerm()){
        term();
    }
    else{
        error("a term");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "+" || token.getLexeme() == "-"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isTerm()){
            term();
        }
        else{
            error("a term");
        }
        token = lexer->peekNextToken();
    }

}

bool Parser::isRelationalExpression(){
    return isArithmeticExpression();
}

/**
 *
 * relationalExpression -> ArithmeticExpression { ( = | > | < ) ArithmeticExpression }
 */
void Parser::relationalExpression(){
    cout << "relation expression - " << token.getLexeme();
    cout << ", peak: relation expression - " << lexer->peekNextToken().getLexeme() << "\n";

    token = lexer->peekNextToken();
    if(isArithmeticExpression()){
        arithmeticExpression();
    }
    else{
        error("an arithmetic expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "=" || token.getLexeme() == ">" || token.getLexeme() == "<"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();

        if(isArithmeticExpression()){
            arithmeticExpression();
        }
        else{
            error("an arithmetic expression");
        }
        token = lexer->peekNextToken();
    }
}

bool Parser::isExpression(){
    return isRelationalExpression();
}

/**
 *
 * expression -> relationalExpression { ( & | | ) relationalExpression }
 */
void Parser::expression(){
    cout << "expression - " << token.getLexeme();
    cout << ", peak: expression - " << lexer->peekNextToken().getLexeme() << "\n";

    token = lexer->peekNextToken();
    if(isRelationalExpression()){
        relationalExpression();
    }
    else{
        error("a relational expression");
    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == "&" || token.getLexeme() == "|"){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
        if(isRelationalExpression()){
            relationalExpression();
        }
        else{
            error("a relational expression");
        }
        token = lexer->peekNextToken();
    }

}

/**
 *
 * returnStatemnt -> return [ expression ] ;
 */
void Parser::returnStatement(){
    cout << "return statement - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "return"){

    }
    else{
        error("'return'");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
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
    cout << "in expression list - " << token.getLexeme() << "\n";

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
            error("an expression");
        }
        token = lexer->peekNextToken();
    }
}

bool Parser::isSubroutineCall(){
    return token.getType() == Token::Identifier;
}

/**
 *
 * subroutineCall -> identifier [ . identifier ] ( expressionList )
 */
void Parser::subroutineCall(){
    cout << "subroutine call - " << token.getLexeme() << "\n";

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
        else{
            error("an identifier");
        }
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    //TODO: check if get next token required
    expressionList();

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
    cout << "do statement - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    token = lexer->peekNextToken();
    if(isSubroutineCall()){
        subroutineCall();
    }
    else{
        error("an identifier");
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
 * whileStatement -> while ( expression ) { {statement} }
 */
void Parser::whileStatement(){
    cout << "while statement - " << token.getLexeme() << "\n";

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
    if(isExpression()){
        expression();
    }
    else{
        error("an expression");
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
    while(isStatement()){
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
    cout << "if statement - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "if"){

    }
    else{
        error("'if'");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    token = lexer->peekNextToken();
    if(isExpression()){
        expression();
    }
    else{
        error("an expression");
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
    while(isStatement()){
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
        while(isStatement()){
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
    cout << "let statement - " << token.getLexeme() << "\n";

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
        if(isExpression()){
            expression();
        }
        else{
            error("an expression");
        }

        token = lexer->getNextToken();
        if(token.getLexeme() == "]"){

        }
        else{
            error("']");
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
    if(isExpression()){
        expression();
    }
    else{
        error("an expression");
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
    cout << "var declare statement - " << token.getLexeme() << "\n";

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
            error("an identifier");
        }
        token = lexer->peekNextToken();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ";"){

    }
    else{
        error("';'");
    }
}

bool Parser::isStatement(){
    return token.getLexeme() == "var" || token.getLexeme() == "let" || token.getLexeme() == "if" || token.getLexeme() == "while" || token.getLexeme() == "do" || token.getLexeme() == "return";
}

/**
 *
 * statement -> varDeclarStatement | letStatemnt | ifStatement | whileStatement | doStatement | returnStatemnt
 */
void Parser::statement(){
    cout << "in statement - " << token.getLexeme() << "\n";

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
        error("a statement");
    }
}

/**
 *
 * subroutineBody -> { {statement} }
 */
void Parser::subroutineBody(){
    cout << "In subroutine body - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "{"){

    }
    else{
        error("'{'");
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
        error("'}'");
    }
}

/**
 *
 * paramList -> type identifier {, type identifier} | ε
 */
void Parser::paramList(){
    cout << "In param list - " << token.getLexeme() << "\n";

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }

    token = lexer->getNextToken();
    if(token.getType() == Token::Identifier){

    }

    token = lexer->peekNextToken();
    while(token.getLexeme() == ","){
        token = lexer->getNextToken();
        token = lexer->peekNextToken();
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
    }
}

/**
 *
 * subroutineDeclar -> (constructor | function | method) (type|void) identifier (paramList) subroutineBody
 */
void Parser::subroutineDeclare() {
    cout << "in subroutine declare - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){

    }
    else{
        error("a subroutine declaration");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }
    else if(token.getLexeme() == "void"){
        token = lexer->getNextToken();
    }
    else{
        error("type or 'void'");
    }

    token = lexer->getNextToken();
    if(token.getType() ==  Token::Identifier){

    }
    else{
        error("an identifier");
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == "("){

    }
    else{
        error("'('");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        paramList();
    }

    token = lexer->getNextToken();
    if(token.getLexeme() == ")"){

    }
    else{
        error("')'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "{"){
        subroutineBody();
    }
    else{
        error("'{'");
    }
}

/**
 *
 * type -> int | char | boolean | identifier
 */
void Parser::type(){
    cout << "in type - " << token.getLexeme() << "\n";

    token = lexer->getNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){

    }
    else{
        error("a var type or identifier");
    }
}

/**
 *
 * classVarDeclar -> (static | field) type identifier {, identifier} ;
 */
void Parser::memberDeclare() {
    cout << "in member declare - " << token.getLexeme() << "\n";
    token = lexer->peekNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){
        classVarDeclare();
    }
    else if(token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){
        subroutineDeclare();
    }
    else{
        error("a class declaration or subroutine declaration");
    }
}

/**
 *
 * memberDeclar -> classVarDeclar | subroutineDeclar
 */
void Parser::classVarDeclare() {
    cout << "in class var declare - " << token.getLexeme() << "\n";
    token = lexer->getNextToken();
    if(token.getLexeme() == "static" || token.getLexeme() == "field"){

    }
    else{
        error("'static' or 'field'");
    }

    token = lexer->peekNextToken();
    if(token.getLexeme() == "int" || token.getLexeme() == "char" || token.getLexeme() == "boolean" || token.getType() == Token::Identifier){
        type();
    }
    else{
        error("a var type or identifier");
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
        error("';'");
    }
}

/**
 *
 * classDeclar -> class identifier { {memberDeclar} }
 */
void Parser::classDeclare() {
    cout << "in Class declare-  - " << token.getLexeme() << "\n";
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
    while(token.getLexeme() == "static" || token.getLexeme() == "field" || token.getLexeme() == "constructor" || token.getLexeme() == "function" || token.getLexeme() == "method"){
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

