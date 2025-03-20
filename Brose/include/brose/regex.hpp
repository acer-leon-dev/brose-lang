#pragma once

#include <string>


namespace brose::regex
{

std::string match_start(
    const std::string& regex,
    const std::string& src,
    std::size_t pos = 0z,
    std::size_t n = std::string::npos);
    
template<typename Iterator>
std::string join_strings_or(Iterator begin, Iterator end)
{
    std::string regex;
    Iterator loop_end = end - 1;
    for (Iterator it = begin; it != loop_end; it++) {
        regex += *it + '|';
    }
    regex += *(--end); 
    return regex;
}

}; // namespace brose