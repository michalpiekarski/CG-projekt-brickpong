#ifndef __Brickpong__BrickpongException__
#define __Brickpong__BrickpongException__

#include <iostream>
#include <exception>

class BrickpongException : public std::exception
{
private:
    std::string _what;
public:
    BrickpongException(std::string what);
    virtual ~BrickpongException();

    virtual const char* what() const throw();
};

#endif /* defined(__Brickpong_ExceptionHandler__) */