// test_Grammar.cpp 
// Created by Robin Rowe 2021-02-17
// MIT License

#include <iostream>
#include "../Grammar.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Grammar" << endl;
	Grammar grammar;
	if(!grammar)
	{	cout << "Grammar failed on operator!" << endl;
		return 1;
	}
	cout << grammar << endl;
	cout << "Grammar Passed!" << endl;
	return 0;
}
