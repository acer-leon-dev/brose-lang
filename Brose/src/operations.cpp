#include "pch.hpp"
#include <brose/operations.hpp>

namespace brose 
{

const binary_operation_type add = [](auto a, auto b) { return a + b; };
const binary_operation_type sub = [](auto a, auto b) { return a - b; };
const binary_operation_type mul = [](auto a, auto b) { return a * b; };
const binary_operation_type div = [](auto a, auto b) { return a / b; };
const binary_operation_type exp = [](auto a, auto b) { return std::pow(a, b); };
const binary_operation_type mod = [](auto a, auto b) { return std::fmod(a, b); };

const unary_operation_type abs    = [](auto a) { return std::abs(a); };
const unary_operation_type fac   = [](auto a) { 
    a = std::floor(a);
    auto result = 1;
    for (int i = 2; i <= a; ++i) {
        result *= i;
    }
    return result;
};


const binary_function_type log = [](auto args) { return std::log10(args[1]) / std::log10(args[0]); };

const function_type ln   = [](auto args) { return std::log(args[0]); };
const function_type sin  = [](auto args) { return std::sin(args[0]); };
const function_type cos  = [](auto args) { return std::cos(args[0]); };
const function_type tan  = [](auto args) { return std::tan(args[0]); };
const function_type floor = [](auto args) { return std::floor(args[0]); };
const function_type ceil = [](auto args) { return std::ceil(args[0]); };

}; // namespace brose