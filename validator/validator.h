
#pragma once
#include <exception>
#include <string>

class Validator{
public:
    static bool str_int(const std::string& s);

    static int string_to_int(const std::string& s);

    static std::string is_string_empty(const std::string& s);
};

///custom exception class
class ValidationException : public std::exception {
private:
    std::string message;

public:
    ValidationException(std::string message) : message(message) {}

    const char* which_message()
    {
        return message.c_str();
    }
};