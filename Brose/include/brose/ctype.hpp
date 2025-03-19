#pragma once

#include <string>

namespace brose
{

// Matches whitespace character except newline
bool isspacenn(char c);   
// Matches any digit (0-9) or period (.)
bool isdigitf(char c);
// Matches any letter, any digit, or period
bool isalnumf(char c);

bool isspacenn_s(std::string str);
bool isdigitf_s(std::string str);    
bool isalnumf_s(std::string str);

}; // namespace brose