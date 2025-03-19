#pragma once

#include "../PCH.hpp"

struct Script
{
private:
    // Some data structure (probably a sequence or tree) that holds the instructions
    // AbstractDataStructure instructions;
public:
    double invoke(double x);
};

Script compileSource(std::string source);