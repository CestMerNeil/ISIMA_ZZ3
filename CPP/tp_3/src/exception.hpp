#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <string>
#include <typeinfo>
#include <cxxabi.h>
#include <demangle.hpp>

class ExceptionChaine : public std::exception
{
private:
    std::string message;

public:
    explicit ExceptionChaine(const std::string &message) : message(message) {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

#endif