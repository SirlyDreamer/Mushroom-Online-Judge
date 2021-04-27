#include <iostream>
#include <string>
#include <syscall.h>
#include <fstream>
#include <sstream>

#define LANG string(argv[1])
#define CODE string(argv[2])
#define INPUT string(argv[3])
using namespace std;

bool saveSourceCode(string str,string lang)
{
    ofstream code;
    if(lang == "c")
        code.open("./source.c");
    if(lang == "cpp")
        code.open("./source.cpp");
    stringstream s;
    s << lang;
    code << s.str();
    code.close();
}

int main(int argc,char* argv[])
{
    if (LANG == "c")
    {

    }
}