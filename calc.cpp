// calc.cpp 
// Created by Robin Rowe 2021-02-17
// MIT License
// Inspired by Chapter 7.8.3 of "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup

#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
using namespace std;

void Usage()
{	cout << "Usage: calc " << endl;
}

enum
{	ok,
	invalid_args

};

void ShowManPage(ostream& os)
{   const char* calc_man_file = "../calc_man.txt";
    ifstream is(calc_man_file);
    if (!is.good())
    {   return;
    }
    ostringstream s;
    s << is.rdbuf();
    os << s.str() << endl;
}

int main(int argc,char* argv[])
{	cout << "calc starting..." << endl;
#if 0
	if(argc < 1)
	{	Usage();
		return invalid_args;
	}
#endif
    ShowManPage(cout);
    const char* example = "> 1 + 2;\n= 3\n> q";
    cout << "Example: " << example << endl;
    const char quit = 'q';    // t.kind==quit means that t is a quit Token
    const char print = ';';    // t.kind==print means that t is a print Token
    Parser parser(cin);        // provides get() and putback() 
    while (parser)
    {   cout << "> ";
        Token token = parser.get();
        if(!token)
        {   cout << "bad token" << endl;
            continue;
        }
        while (token.kind == print) 
        {   token = parser.get();    // first discard all "prints"
        }
        if (token.kind == quit) 
        {   break;        // quit
        }
        parser.putback(token);
        double total = parser.statement();
        cout << "= " << total << endl;
    }
	cout << "calc done!" << endl;
	return ok;
}

/*
*/

