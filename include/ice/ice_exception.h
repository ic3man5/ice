#pragma once

#include <stdexcept>
#include <string>

namespace ice {
class Exception;
};

class ice::Exception : public std::exception {
    const std::string m_msg;

public:
    Exception(const std::string msg)
        : m_msg(msg)
    {
    }
    ~Exception() throw() { }
    Exception operator=(Exception&) = delete;
    const char *what() const throw() { return this->m_msg.c_str(); }
    std::string const whatString() const { return this->m_msg; }
};
