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

Token getNextToken(ifstream& file, int& lineNum){
    char ch;
    
    while(file.get(ch)){
        if(ch=='\n'){ lineNum++;}
        else if(ch==' '||ch=='\t'){continue;}
        else if(ch=='/'){
            char nextCh;
            if(file.get(nextCh)){
                if(nextCh=='/'){
                    while(file.get(nextCh) && nextCh!='\n');
                    if(nextCh=='\n') lineNum++;
                }
                else if(nextCh=='*'){
                    char prev=0;
                    while(file.get(ch)){
                        if(ch=='\n') lineNum++;
                        if(prev=='*' && ch=='/') break;
                        prev=ch;
                    }
                }
                else{
                    file.unget();
                    return{TOKEN_OPERATOR, "/", lineNum};
                }
            }
        }
        else{break;}
    }
    if(file.eof()){
        return {TOKEN_EOF, "EOF", lineNum};
    }
}


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
        cout<<"Line "<<t.line<<" | "<<tokenTypeToString(t.type)<<" : "<<t.lexeme<<endl;
    }


    sourceFile.close();

    return 0;
}