#include "pch.hpp"
#include <brose/ctype.hpp>

namespace 
{

bool validate_predicate_string(std::function<bool(char)> pred, const std::string& str)
{
    for (char c : str) 
    {
        if (!pred(c)) {
                return false;
        }
    }
    return true;
}

}; // {anonymous} namespace

namespace brose 
{

// Chars

bool isspacenn(char c) 
{
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}
    
bool isdigitf(char c)
{
    return std::isdigit(c) || c == '.';
}
    
bool isalnumf(char c)
{
    return std::isalnum(c) || c == '.';
}

// Strings

bool isspacenn_s(std::string str)
{
    return validate_predicate_string(isspacenn, str);
}

bool isdigitf_s(std::string str)
{
    return validate_predicate_string(isdigitf, str);
}
    
bool isalnumf_s(std::string str)
{
    return validate_predicate_string(isalnumf, str);
}

}; // namespace brose