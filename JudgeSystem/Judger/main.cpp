#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

enum{c = 0, cpp, java, python3, kotlin};//python3 ang kotlin is not supported right now (QwQ)

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
	dev.source = "source.cpp";
	dev.cpuLimit = 2;
	dev.memLimit = 256;
	dev.casenum = 1;
	dev.cases = "./cases/";
	return dev;
}

void initEnv (string source)
{
	command[c] = "gcc -g -O2 -std=gnu11 -static " + source + " -lm &> compile.res";
	command[cpp] = "g++ -g -O2 -std=gnu++17 -static " + source +" &> compile.res";
	command[java] = "javac -encoding UTF-8 -sourcepath . -d . " + source + " &> compile.res";
	command[python3] = "pypy3 -m py_compile " + source + " &> compile.res";
	command[kotlin] = "kotlinc -d . " + source + " &> compile.res";
}

bool isCE()
{
	fstream res;
	bool ce;
	string line;
	res.open("./compile.res",ios::in);
	if(!res.is_open())
	{
		cout << "System Error" << endl;
		return true;
	}
	while(!res.eof())
	{
		res >> line;
		if(line.size() == 0)
			continue;
		if(line.find("error")!=line.size())
			return true;
	}
	res.close();
	return false;
}

int main ()
{
	config src;
	src = getConfig();
	initEnv(src.source);
	system(command[src.lang].c_str());
	if(isCE())
	{
		ifstream errorinfo("./compile.res");
		char buffer[130];
		if(!errorinfo.is_open())
		{
			cout << "System Error" << endl;
			return 0;
		}
		cout << "Compile Error" << endl;
		while(!errorinfo.eof())
		{
			errorinfo.getline(buffer,128);
			cout << buffer << endl;
		}
		return 0;
	}
	return 0;
}