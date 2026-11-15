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



}

public:
    Parser(vector<Token> tokenList){
        tokens=tokenList;
        position=0;
    }
    void parseProgram(){

    }
