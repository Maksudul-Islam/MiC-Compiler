#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "lexer.hpp"

using namespace std;

class Parser{
private:
    vector<Token> tokens;
    int position;

    Token currentToken(){
        if(position<tokens.size()){return tokens[position];}
        return {TOKEN_EOF, "EOF", tokens.empty() ? 1 : tokens.back().line};
    }
    void nextPosition(){
        if(position<tokens.size()){position++;}
    }
    void match(TokenType expectedType, string expectedLexeme=""){
        Token t=currentToken();
        if(t.type==expectedType && (expectedLexeme==""||t.lexeme==expectedLexeme)){
            nextPosition();
        }
        else{
            cout<<"Syntax Error at Line "<<t.line<<".";
            exit(1);
        }
    }

    void parseExpresssion(){
        
    }

    void parseDeclaration(){

    }
    void parseAssignment(){

    }
    void parseIfStatement(){

    }
    void parseReturn(){

    }

    void parseStatement(){
        Token t=currentToken();
        if(t.type==TOKEN_KEYWORD && (t.lexeme=="int"||t.lexeme=="float"||t.lexeme=="double"||t.lexeme=="char")){
            parseDeclaration();
        }
        else if(t.type==TOKEN_INDENTIFIER){
            parseAssignment();
        }
        else if(t.type==TOKEN_KEYWORD && t.lexeme=="if"){
            parseIfStatement();
        }
        else if(t.type==TOKEN_KEYWORD && t.lexeme=="return"){
            parseReturn();
        }
        else{
            cout<<"Syntax Error at Line: "<<t.line<<".";
            exit(1);
        }
    }


public:
    Parser(vector<Token> tokenList){
        tokens=tokenList;
        position=0;
    }
    void parseProgram(){
        match(TOKEN_KEYWORD,"int");
        match(TOKEN_INDENTIFIER,"main");
        match(TOKEN_SYMBOL,"(");
        match(TOKEN_SYMBOL,")");
        match(TOKEN_SYMBOL,"{");
        while(currentToken().lexeme!="}" && currentToken().type!=TOKEN_EOF){
                parseStatement();
        }
        match(TOKEN_SYMBOL,"}");
        cout<<"Syntex Analysis Successful: No Syntax Errors Found!"<<endl;
    }
};