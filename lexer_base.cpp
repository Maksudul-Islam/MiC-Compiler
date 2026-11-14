#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum TokenType{
    TOKEN_KEYWORD,
    TOKEN_INDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_OPERATOR,
    TOKEN_SYMBOL,
    TOKEN_EOF,
    TOKEN_UNKNOWN
};

struct Token{
    TokenType type;
    string lexeme;
    int line;
};


int main(){
    
    //use in final code
    //string filename;
    //cout<<"Enter the source file name: "; cin>>filename;

    //ifstream sourceFile(filename);
    fstream sourceFile("test.c");
    if(!sourceFile.is_open()){
        cout<<"Error: File could not be opened."<<endl;
        return 1;
    }

    int lineNum=1;
    vector<Token> tokens;

    cout<<"Lexical Analysis..."<<endl;
    while(true){
        Token t=getNextToken(sourceFile, lineNum);

        if(t.type==TOKEN_EOF) break;

        tokens.push_back(t);
    }


    sourceFile.close();

    return 0;
}