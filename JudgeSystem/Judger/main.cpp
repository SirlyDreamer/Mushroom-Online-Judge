#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

enum{c = 0, cpp, java, python3, kotlin};

struct config
{
	int lang;    //The language
	string source;  //The path of source code
	int cpuLimit;   //Frequency(GHz) * Time(s)
	int memLimit;   //MiB
	int casenum;    //The number of test cases;
	string cases;   //The path of test cases;
};

const int lannum = 5;
string command[lannum];

config getConfig()
{
	//TODO:Read config from file or network
	//To test
	config dev;
	dev.lang = cpp;
	dev.source = "./source.cpp";
	dev.cpuLimit = 2;
	dev.memLimit = 256;
	dev.casenum = 1;
	dev.cases = "./cases/";
	return dev;
}

void initEnv (string source)
{
	command[c] = "gcc -g -O2 -std=gnu11 -static " + source + " -lm";
	command[cpp] = "g++ -g -O2 -std=gnu++17 -static " + source;
	command[java] = "javac -encoding UTF-8 -sourcepath . -d . " + source;
	command[python3] = "pypy3 -m py_compile " + source;
	command[kotlin] = "kotlinc -d . " + source;
}

int main ()
{
	config src;
	src = getConfig();
	initEnv(src.source);

}