#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

enum TokenType{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
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

bool isKeyword(const string& word){
    vector<string> keywords={"int", "float", "double", "char","if", "else", "while", "for", "return", "void"};
    return find(keywords.begin(),keywords.end(),word) !=keywords.end(); 
}
bool isSymbol(char ch){
    string symbols=";,(){}[]";
    return symbols.find(ch) != string::npos;
}
bool isOperatorChar(char ch){
    string ops="+-*/=<>!&|";
    return ops.find(ch) != string::npos;
}


Token getNextToken(ifstream& file, int& lineNum){
    char ch;
    
    while(file.get(ch)){
        if(ch=='\n'){ lineNum++;}
        else if(isspace(ch)){continue;}
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

    if(isalpha(ch) || ch=='_'){
        string word;    word+=ch;
        while(file.get(ch) && (isalnum(ch) || ch=='_')){
            word+=ch;
        }
        if(!file.eof()){file.unget();}

        if(isKeyword(word)){
            return {TOKEN_KEYWORD, word, lineNum};
        }
        return {TOKEN_IDENTIFIER, word, lineNum};
    }
    
    if(isdigit(ch)){
        string num;     num+=ch;
        bool hasDot=false;
        while(file.get(ch) && (isdigit(ch) || (ch=='.' && !hasDot))){
            if(ch=='.'){hasDot=true;}
            num+=ch;
        }
        if(!file.eof()){file.unget();}
        return {TOKEN_CONSTANT, num, lineNum};
    }

    if(isOperatorChar(ch)){
        string op;      op+=ch;
        char nextCh;
        if(file.get(nextCh)){
            if((ch=='=' || ch=='!' || ch=='<'||ch=='>') && nextCh=='='){
                op+=nextCh;
            }
            else if((ch=='&'&&nextCh=='&') || (ch=='|'&&nextCh=='|')){
                op+=nextCh;
            }
            else{file.unget();}
        }
        return {TOKEN_OPERATOR, op, lineNum};
    }

    if(isSymbol(ch)){
        string sym(1,ch);
        return {TOKEN_SYMBOL, sym, lineNum};
    }

    string unknown(1,ch);
    return{TOKEN_UNKNOWN, unknown, lineNum};
}

string tokenTypeToString(TokenType type){
    switch(type){
        case TOKEN_KEYWORD: return "KEYWORD";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_CONSTANT: return "CONSTANT";
        case TOKEN_OPERATOR: return "OPERATOR";
        case TOKEN_SYMBOL: return"SYMBOL";
        case TOKEN_UNKNOWN: return"UNKNOWN";
        case TOKEN_EOF: return"EOF";
        default: return "UNKNOWN";
    }
}
