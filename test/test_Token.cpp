// test_Token.cpp 
// Created by Robin Rowe 2021-02-17
// MIT License

#include <iostream>
#include "../Token.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Token" << endl;
	Token token;
	if(!token)
	{	cout << "Token failed on operator!" << endl;
		return 1;
	}
	cout << token << endl;
	cout << "Token Passed!" << endl;
	return 0;
}
