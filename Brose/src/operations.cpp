#include "pch.hpp"
#include <brose/operations.hpp>

namespace brose::operations
{

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    return a / b;
}

double exp(double a, double b) {
    return std::pow(a, b);
}

double mod(double a, double b) {
    return std::fmod(a, b);
}

double abs(double x) {
    return std::abs(x); 
}

double fac(double x) {
    x = std::floor(x);
    double result = 1;
    for (int i = 2; i <= x; ++i) {
        result *= i;
    }
    return result;
}

double log(const std::vector<double>& args) {
    return std::log10(args[1]) / std::log10(args[0]); 
}

double ln(const std::vector<double>& args) {
    return std::log(args.at(0)); 
}

double sin(const std::vector<double>& args) {
    return std::sin(args.at(0)); 
}

double cos(const std::vector<double>& args) {
    return std::cos(args.at(0)); 
}

double tan(const std::vector<double>& args) {
    return std::tan(args.at(0)); 
}

double floor(const std::vector<double>& args) {
    return std::floor(args.at(0)); 
}

double ceil(const std::vector<double>& args) {
    return std::ceil(args.at(0)); 
}


}; // namespace brose::operations