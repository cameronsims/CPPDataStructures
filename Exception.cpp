// Exception.cpp

#include "Exception.h"

const char* cslib::Exception::what() const throw() { return "Exception Thrown."; }
const char* cslib::OutOfRange::what() const throw() { return "Index out of range."; }