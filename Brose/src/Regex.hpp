#pragma once

#include "PCH.hpp"

namespace regex
{

std::string match_start(
    const std::string& regex,
    const std::string& src,
    std::size_t pos = 0z,
    std::size_t n = std::string::npos);
    
template<typename Iterator>
std::string join_regex_or(Iterator begin, Iterator end)
{
    std::string regex;
    while (begin != end - 1) {
        regex += *begin + '|';
        begin++;
    }
    regex += *(--end); 
    return regex;
}

};