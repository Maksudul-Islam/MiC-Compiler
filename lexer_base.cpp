#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

    string filename;
    cout<<"Enter the source file name: "; cin>>filename;

    ifstream sourceFile(filename);
    if(!sourceFile.is_open()){
        cout<<"Error: File could not be opened."<<endl;
        return 1;
    }

    cout<<"File Reading..."<<endl;
    char ch;
    while(sourceFile.get(ch)){
        //
        cout<<ch;
    }

    sourceFile.close();

    return 0;

}