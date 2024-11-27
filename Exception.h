#ifndef CSEXCEPTION_H
#define CSEXCEPTION_H

#include <exception>

namespace cslib {
    class Exception : public std::exception {
        virtual const char* what() const throw();
    };

    class OutOfRange : public Exception {
        virtual const char* what() const throw();
    };
}

#endif