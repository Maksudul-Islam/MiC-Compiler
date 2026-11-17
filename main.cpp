#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "semantic.hpp"

using namespace std;

int main(){
    
    //use in final code
    //string filename;
    //cout<<"Enter the source file name: "; cin>>filename;

    //ifstream sourceFile(filename);
    ifstream sourceFile("input.c");
    if(!sourceFile.is_open()){
        cout<<"Error: File could not be opened."<<endl;
        return 1;
    }

    int lineNum=1;
    vector<Token> tokens;

    while(true){
        Token t = getNextToken(sourceFile, lineNum);
        tokens.push_back(t);
        if(t.type==TOKEN_EOF) break;

        cout<<"Line "<<t.line<<" | "<<tokenTypeToString(t.type)<<" : "<<t.lexeme<<endl;

    }
    cout<<endl;

    sourceFile.close();

    Parser parser(tokens);
    parser.parseProgram();

    SemanticAnalyzer semantic(tokens);
    semantic.analyzerProgram();

    return 0;
}
