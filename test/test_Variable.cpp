// test_Variable.cpp 
// Created by Robin Rowe 2021-02-17
// MIT License

#include <iostream>
#include "../Variable.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Variable" << endl;
	Variable variable;
	if(!variable)
	{	cout << "Variable failed on operator!" << endl;
		return 1;
	}
	cout << variable << endl;
	cout << "Variable Passed!" << endl;
	return 0;
}
