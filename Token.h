// Token.h 
// Created by Robin Rowe 2021-02-17
// MIT License

#ifndef Token_h
#define Token_h

#include <iostream>
#include <string>

class Token
{//	Token(const Token&) = delete;
//	void operator=(const Token&) = delete;

public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	std::string name; // for names: name itself
	~Token()
	{}
	Token()
	:	kind(0)
	,	value(0) 
	{}
	Token(char ch)
	:	kind(ch)
	,	value(0)
	{}
	Token(char kind, double value)
	:	kind(kind)
	,	value(value)
	{}
	Token(char kind, const std::string& name)
	:	kind(kind)
	,	value(0)
	,	name(name)
	{}
	bool operator!() const
	{	return false;
	}
	std::ostream& Print(std::ostream& os) const;
	std::istream& Input(std::istream& is);
};

inline
std::ostream& operator<<(std::ostream& os,const Token& token)
{	return token.Print(os);
}


inline
std::istream& operator>>(std::istream& is,Token& token)
{	return token.Input(is);
}

#endif
