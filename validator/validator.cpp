
#include "validator.h"
#include <algorithm>

bool Validator::str_int(const std::string &s)
///checks if it can convert a string to an int
///returns true if it can be converted, false otherwise
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int Validator::string_to_int(const std::string &s)
///converts a string to an int
///returns the string converted in int
///throws exception if it's not possible
{
    if (!str_int(s))
        throw ValidationException("Cannot convert string to int!");
    return std::stoi(s);
}

std::string Validator::is_string_empty(const std::string &s)
///checks if a string is empty
///returns the string if it's not empty, throws ValidationException otherwise
{
    if (s.empty())
        throw ValidationException("String cannot be empty!");
    return s;
}