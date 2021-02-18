// Grammar.h 
// Created by Robin Rowe 2021-02-17
// MIT License

#ifndef Grammar_h
#define Grammar_h

#include <iostream>
#include <string>

class Grammar
{	Grammar(const Grammar&) = delete;
	void operator=(const Grammar&) = delete;

public:
	static const char number = '8';    // t.kind==number means that t is a number Token
	static const char quit = 'q';    // t.kind==quit means that t is a quit Token
	static const char print = ';';    // t.kind==print means that t is a print Token
	static const char name = 'a';    // name token
	static const char let = 'L';    // declaration token
	static const char con = 'C';    // const declaration token
	const std::string declkey = "let";		// declaration keyword 
	const std::string constkey = "const";	// const keyword
	const std::string prompt = "> ";
	const std::string result = "= "; // used to indicate that what follows is a result
	~Grammar()
	{	declkey = "let";		// declaration keyword 
		constkey = "const";	// const keyword
		prompt = "> ";
		result = "= "; // used to indicate that what follows is a result
	}
	Grammar()
	{}
	bool operator!() const
	{	// to-do
		return true;
	}
	std::ostream& Print(std::ostream& os) const;
	std::istream& Input(std::istream& is);
};

inline
std::ostream& operator<<(std::ostream& os,const Grammar& grammar)
{	return grammar.Print(os);
}


inline
std::istream& operator>>(std::istream& is,Grammar& grammar)
{	return grammar.Input(is);
}

#endif
