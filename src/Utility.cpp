#include <iostream>
#include "Utility.h"
#include "Token.h"
#include "Token_stream.h"

// Helper function to show an error message
inline void error(const std::string& errormessage)
{
    std::cerr << errormessage << std::endl;
    throw std::runtime_error(errormessage);
}

inline void error(std::string s1, std::string s2)
{
    error(s1+s2);
}

// deal with + and -
double expression(Token_stream ts)
{
    double left = term(ts);      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
            case '+':
                left += term(ts);    // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(ts);    // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more + or -: return the answer
        }
    }
}

// deal with *, /, and %
double term(Token_stream ts)
{
    double left = primary(ts);
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
            case '*':
                left *= primary(ts);
                t = ts.get();
                break;
            case '/':
            {
                double d = primary(ts);
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);     // put t back into the token stream
                return left;
        }
    }
}

// deal with numbers and parentheses
double primary(Token_stream ts)
{
    Token t = ts.get();

    switch (t.kind) {
        case '(':    // handle '(' expression ')'
        {
            double d = expression(ts);
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '8':            // we use '8' to represent a number
            return t.value;  // return the number's value
        default:
            error("primary expected");
    }

    bool temp = false;
    return temp;

}
