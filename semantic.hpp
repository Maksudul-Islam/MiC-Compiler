#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "lexer.hpp"

using namespace std;

class SemanticAnalyzer{
private:
    vector<Token> tokens;
    int position;

    Token currentToken(){
        if(position<tokens.size()){return tokens[position];}
        return {TOKEN_EOF,"EOF", tokens.empty()  ?  1 : tokens.back().line};
    }
    
    void nextPosition(){
        if(position<tokens.size()){position++;}
    }

void analyzeDeclaration(){

}
void analizeAssignment(){

}
void analizeIfStatement(){

}
void analyzeReturn(){
    
}


void analysisStatement(){
    Token t=currentToken();
    if(t.type==TOKEN_KEYWORD && (t.lexeme=="int"||t.lexeme=="float"||t.lexeme=="double"||t.lexeme=="char")){
        analyzeDeclaration();
    }
    else if(t.type==TOKEN_IDENTIFIER){
        analizeAssignment();
    }
    else if(t.type==TOKEN_KEYWORD && t.lexeme=="if"){
        analizeIfStatement();
    }
    else if(t.type==TOKEN_KEYWORD && t.lexeme=="return"){
        analyzeReturn();
    }
}

public:
    SemanticAnalyzer(vector<Token> tokenList){
        tokens=tokenList;
        position=0;
    }

    void analyzerProgram(){
        int i=5;
        while(i--){
            nextPosition();
        }
        while(currentToken().lexeme!="}" && currentToken().type!=TOKEN_EOF){
            analysisStatement();
        }
        nextPosition();
        cout<<"Semantic Analysis Successful: No Semantic Errors Found!"<<endl;
    }

};