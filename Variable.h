// Variable.h 
// Created by Robin Rowe 2021-02-17
// MIT License

#ifndef Variable_h
#define Variable_h

#include <iostream>
#include <string>

class Variable
{//	Variable(const Variable&) = delete;
//	void operator=(const Variable&) = delete;

public:
	std::string name;
	double value;
	bool var;	// variable (true) or constant (false)
	~Variable()
	{}
	Variable(const std::string& n, double v, bool va = true) 
	:	name(n)
	,	value(v)
	,	var(va) 
	{}
	Variable()
	:	value(0)
	,	var(false)
	{}
	bool operator!() const
	{	return false;
	}
	std::ostream& Print(std::ostream& os) const;
	std::istream& Input(std::istream& is);
};

inline
std::ostream& operator<<(std::ostream& os,const Variable& variable)
{	return variable.Print(os);
}


inline
std::istream& operator>>(std::istream& is,Variable& variable)
{	return variable.Input(is);
}

#endif
