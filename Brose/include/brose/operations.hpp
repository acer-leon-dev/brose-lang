#include <functional>

namespace brose 
{

using unary_operation = std::function<double(double)>;
using binary_operation = std::function<double(double, double)>;
using unary_function = unary_operation;
using binary_function = binary_operation;

const extern binary_operation add;
const extern binary_operation sub;
const extern binary_operation mul;
const extern binary_operation div;
const extern binary_operation exp;
const extern binary_operation mod;

const extern unary_operation abs;
const extern unary_operation fac;

const extern binary_function log;

const extern unary_function ln;
const extern unary_function sin;
const extern unary_function cos;
const extern unary_function tan;
const extern unary_function floor;
const extern unary_function ceil;

}; // namespace brose