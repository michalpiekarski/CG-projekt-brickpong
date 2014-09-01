#include "BrickpongException.h"

BrickpongException::BrickpongException(std::string what) {
    _what = what;
}

BrickpongException::~BrickpongException() throw() {
    std::exception::~exception();
}

const char* BrickpongException::what() const throw() {
    return _what.c_str();
}