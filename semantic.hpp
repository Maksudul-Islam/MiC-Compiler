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




public:
    SemanticAnalyzer(vector<Token> tokenList){
        tokens=tokenList;
        position=0;
    }

    void analyzerProgram(){

    }

};