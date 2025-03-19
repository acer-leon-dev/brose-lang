#include "pch.hpp"
#include <brose/operations.hpp>

namespace brose 
{

const binary_operation add = [](auto a, auto b) { return a + b; };
const binary_operation sub = [](auto a, auto b) { return a - b; };
const binary_operation mul = [](auto a, auto b) { return a * b; };
const binary_operation div = [](auto a, auto b) { return a / b; };
const binary_operation exp = [](auto a, auto b) { return std::pow(a, b); };
const binary_operation mod = [](auto a, auto b) { return std::fmod(a, b); };

const unary_operation abs    = [](auto a) { return std::abs(a); };
const unary_operation fac   = [](auto a) { 
    a = std::floor(a);
    auto result = 1;
    for (int i = 2; i <= a; ++i) {
        result *= i;
    }
    return result;
};

const binary_function log = [](auto a, auto b) { return std::log10(b) / std::log10(a); };

const unary_function ln   = [](auto a) { return std::log(a); };
const unary_function sin  = [](auto a) { return std::sin(a); };
const unary_function cos  = [](auto a) { return std::cos(a); };
const unary_function tan  = [](auto a) { return std::tan(a); };
const unary_function floor = [](auto a) { return std::floor(a); };
const unary_function ceil = [](auto a) { return std::ceil(a); };

}; // namespace brose