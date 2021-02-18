// test_Parser.cpp 
// Created by Robin Rowe 2021-02-17
// MIT License

#include <iostream>
#include <sstream>
#include "../Parser.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Parser" << endl;
	std::istringstream is("1 + 2;");
	Parser parser(is);
	if(!parser)
	{	cout << "Parser failed on operator!" << endl;
		return 1;
	}
	cout << parser << endl;
	cout << "Parser Passed!" << endl;
	return 0;
}
