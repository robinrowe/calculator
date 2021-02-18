// Parser.cpp
// Created by Robin Rowe 2021-02-17
// MIT License

#include "Parser.h"
using namespace std;

ostream& Parser::Print(ostream& os) const
{	// to-do
	return os << "Parser";
} 

istream& Parser::Input(std::istream& is) 
{	// to-do
	return is;
}

void Parser::ignore(char c)
// c represents the kind of a Token
{
    // first look in buffer:
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (is >> ch)
        if (ch == c) return;
}

Token Parser::get()
{
    if (full) {         // check if we already have a Token ready
        full = false;
        return buffer;
    }

    char ch;
    is >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)
    if (IsToken(ch))
    {
        return Token(ch); // let each character represent itself
    }
    if (IsNumber(ch))
    {
        is.putback(ch);// put digit back into the input stream
        double val;
        is >> val;     // read a floating-point number
        return Token(number, val);
    }
    if (isalpha(ch)) {	// start with a letter
        string s;
        s += ch;
        while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;	// letters digits and underscores
        is.putback(ch);
        if (s == declkey) return Token(let); // keyword "let"
        if (s == constkey) return Token(con); // keyword "const"
        return Token(name, s);
    }
    return Token(); // error("Bad token");
}

bool Parser::primary(double& d)
{
    Token t = get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
    {
        d = expression();
        t = get();
        if (t.kind != ')')
        {   return false; // error("')' expected");
        }
        return true;
    }
    case number:
        d = t.value;    // return the number's value
        return true;
    case name:
    {
        Token next = get();
        if (next.kind == '=') {	// handle name = expression
            d = expression();
            set_value(t.name, d);
            return true;
        }
        putback(next);		// not an assignment: return the value
        d = get_value(t.name); // return the variable's value
        return true;
    }
    case '-':
    {   double x = 0;
        primary(x);
        x = -x;
        return true;
    }
    case '+':
        return primary(d);
    default:
        return false; // error("primary expected");
    }
}

// deal with *, /, and %
double Parser::term()
{   double left = 0;
    primary(left);
    Token t = get(); // get the next token from token stream
    while (true) 
    {   switch (t.kind) 
        {   case '*':
            {   double x = 0;
                primary(x);
                left *= x;
                t = get();
                break;
            }
            case '/':
            {   double d = 0;
                primary(d);
                if (d == 0) 
                {   // error("divide by zero");
                    left = NAN;
                }
                else
                {   left /= d;
                }
                t = get();
                break;
            }
            case '%':
            {
                int i1 = static_cast<int>(left);
                int i2 = static_cast<int>(term());
                if (i2 == 0) 
                {   //error("%: divide by zero");
                    left = NAN;
                }
                else
                {   left = i1 % i2;
                }
                t = get();
                break;
            }
            default:
                putback(t);        // put t back into the token stream
                return left;
        }
    }
}

// deal with + and -
double Parser::expression()
{
    double left = term();      // read and evaluate a Term
    Token t = get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = get();
            break;
        default:
            putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double Parser::declaration(Token k)
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
// k will be "let" or "con"(stant)
{
    Token t = get();
    if (t.kind != name)
    {   // error("name expected in declaration");
        return 0;
    }
    string var_name = t.name;

    Token t2 = get();
    if (t2.kind != '=') 
    {   // error("= missing in declaration of ", var_name);
        return 0;
    }
    double d = expression();
    define_name(var_name, d, k.kind == let);
    return d;
}

double Parser::statement()
{
    Token t = get();
    switch (t.kind) {
    case let:
    case con:
        return declaration(t.kind);
    default:
        putback(t);
        return expression();
    }
}

