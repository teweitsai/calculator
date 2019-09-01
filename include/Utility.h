#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include "Token_stream.h"

// Helper function to show an error message
void error(const std::string&);
void error(std::string, std::string);

// declaration so that primary() can call expression()
double expression(Token_stream& ts);

// deal with *, /, and %
double term(Token_stream& ts);

// deal with numbers and parentheses
double primary(Token_stream& ts);

#endif