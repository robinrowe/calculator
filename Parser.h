// Parser.h 
// Created by Robin Rowe 2021-02-17
// MIT License

#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <vector>
#include <string.h>
#include "Token.h"
#include "Variable.h"

class Parser
{	Parser(const Parser&) = delete;
	void operator=(const Parser&) = delete;
    std::istream& is;
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
	std::vector<Variable> var_table;
    double variable;
    bool isQuit;
    enum
    {   error = 0,
        number = '8',    // t.kind==number means that t is a number Token
        quit = 'q',    // t.kind==quit means that t is a quit Token
        print = ';',    // t.kind==print means that t is a print Token
        name = 'a',    // name token
        let = 'L',    // declaration token
        con = 'C'
    };
    bool IsToken(char ch)
    {   const char* tokens = "q;()+-*/%=";
        return 0 != strchr(tokens,ch);
    }
    bool IsNumber(char ch)
    {   const char* numbers = ".0123456789"; // a floating-point literal can start with a dot
        return 0 != strchr(numbers, ch);
    }
    std::string declkey = "let";	// declaration keyword 
    std::string constkey = "const";	// const keyword
    bool get_value(const std::string& s)  // return the value of the Variable names s
    {   for (int i = 0; i < var_table.size(); ++i)
        {   if (var_table[i].name == s) 
            {   variable = var_table[i].value;
                return true;
        }   }
        return false;
    }
    bool set_value(const std::string s, double d) // set the Variable named s to d
    {   for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s) {
            if (var_table[i].var == false) 
            {   return false; // error(s, " is a constant");
            }
            var_table[i].value = d;
            return true;
        }
        return false;
    }
    bool is_declared(const std::string var) // is var already in var_table?
    {   for (int i = 0; i < var_table.size(); ++i)
        {   if (var_table[i].name == var) 
            {   return true;
        }   }
        return false;
    }
    bool define_name(const std::string s, double val, bool var = true) // add (s,val,var) to var_table
    {   if (is_declared(s)) 
        {   return false;// error(s, " declared twice");
        }      
        var_table.push_back(Variable(s, val, var));
        return true;
    }
public:
	~Parser()
	{}
	Parser(std::istream& is) 	// it reads from is
	:	full(false)
	,	buffer(0)    // no Token in buffer
    ,   isQuit(false)
    ,   is(is)
	{   variable = 0.;
        declkey = "let";		// declaration keyword 
        constkey = "const";	// const keyword
        define_name("pi", 3.1415926535, false);	// these pre-defiend names are constants
        define_name("e", 2.7182818284, false);
	}
	operator bool() const
	{	return !isQuit;
	}
	std::ostream& Print(std::ostream& os) const;
	std::istream& Input(std::istream& is);
    bool primary(double& d);
    double term();
    double expression();
    double declaration(Token k);
    double statement();
    Token get();
    bool putback(Token t)    // put a Token back
    {   if (full)
        {   return false; //error("putback() into a full buffer");
        }
        buffer = t;       // copy t to buffer
        full = true;      // buffer is now full
        return true;
    }
    void ignore(char c);      // discard tokens up to an including a c
};

inline
std::ostream& operator<<(std::ostream& os,const Parser& parser)
{	return parser.Print(os);
}


inline
std::istream& operator>>(std::istream& is,Parser& parser)
{	return parser.Input(is);
}

#endif
