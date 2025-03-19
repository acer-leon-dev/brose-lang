#pragma once

#include "pch.hpp"

namespace brose
{
    
struct Script
{
private:
    // Some data structure (probably a sequence or tree) that holds the instructions
    // AbstractDataStructure instructions;
public:
    double invoke(double x);
};

Script compileSource(std::string source);

}; // namespace brose