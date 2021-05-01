#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

enum
{
	c = 0, cpp, java, python3, kotlin
};//python3 ang kotlin is not supported right now (QwQ)

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

config getConfig ()
{
	//TODO:Read config from file or network
	//To test
	config dev;
	dev.lang = cpp;
	dev.source = "./judge/source.cpp";
	dev.cpuLimit = 2;
	dev.memLimit = 256;
	dev.casenum = 1;
	dev.cases = "./judge/cases/";
	return dev;
}

void initEnv (string source)
{
	command[c] = "gcc -g -O2 -std=gnu11 -static " + source + " -lm -o source 2> compile.txt";
	command[cpp] = "g++ -g -O2 -std=gnu++17 -static " + source + "-o source 2> compile.txt";
	command[java] = "javac -encoding UTF-8 -sourcepath . -d . " + source + " 2> compile.txt";
	command[python3] = "pypy3 -m py_compile " + source + " 2> compile.txt";
	command[kotlin] = "kotlinc -d . " + source + " 2> compile.txt";
}

bool isCE ()
{
	ifstream res ("./compile.txt");
	char buffer[256];
	string line;
	if (!res.is_open ())
	{
		cout << "System Error" << endl;
		return true;
	}
	while (!res.eof ())
	{
		line.clear ();
		res.getline (buffer, 255);
		line = string (buffer);
		if (line.length () == 0)
			continue;
		if (line.find ("error") != string::npos)
			return true;
	}
	res.close ();
	return false;
}

int main ()
{
	config src;
	src = getConfig ();
	initEnv (src.source);
	system (command[src.lang].c_str ());
	if (isCE ())
	{
		cout << "Compile Error" << endl;
	}
	else
	{
		cout << "Compile Successfully!" << endl;
	}
	ifstream errorinfo ("./compile.txt");
	char buffer[256];
	if (!errorinfo.is_open ())
	{
		cout << "System Error" << endl;
		return 0;
	}
	while (!errorinfo.eof ())
	{
		errorinfo.getline (buffer, 255);
		cout << buffer << endl;
	}


	return 0;
}