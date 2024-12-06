#ifndef CSEXCEPTION_H
#define CSEXCEPTION_H

#include <exception>

namespace cslib {
    /**
     * @class Exception
     * @brief Thrown when we run into an exception
     **/
    class Exception : public std::exception {
    public:
        /**
         * @brief Explaination of the node error
         * @return String of the node error explaination
         */
        virtual const char* what() const throw() = 0;
    };

    /**
     * @class OutOfRange
     * @brief Thrown when we can't find a place in a range
     **/
    class OutOfRange : public Exception {
    public:
        const char* what() const throw();
    };
}


#endif