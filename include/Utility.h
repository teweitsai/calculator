#include <iostream>
#include <Token_stream.h>

// Helper function to show an error message
inline void error(const std::string&) {}
inline void error(std::string, std::string) {}

// declaration so that primary() can call expression()
double expression(Token_stream) {}

// deal with *, /, and %
double term(Token_stream) {}

// deal with numbers and parentheses
double primary(Token_stream) {}
