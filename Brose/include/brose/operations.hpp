#include <vector>

namespace brose::operations
{

using unary = double(*)(double);
using binary = double(*)(double, double);
using function = double(*)(const std::vector<double>&);

double add(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div(double a, double b);
double exp(double a, double b);
double mod(double a, double b);

double abs(double x);
double fac(double x);

double log(const std::vector<double>& x);

double ln(const std::vector<double>& x);
double sin(const std::vector<double>& x);
double cos(const std::vector<double>& x);
double tan(const std::vector<double>& x);
double floor(const std::vector<double>& x);
double ceil(const std::vector<double>& x);

}; // namespace brose::operations