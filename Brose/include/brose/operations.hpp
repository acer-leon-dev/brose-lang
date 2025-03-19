#include <functional>
#include <vector>

namespace brose 
{

using unary_operation_type = std::function<double(double)>;
using binary_operation_type = std::function<double(double, double)>;
using function_type = std::function<double(std::vector<double>)>;
using function_type = function_type;
using binary_function_type = function_type;

const extern binary_operation_type add;
const extern binary_operation_type sub;
const extern binary_operation_type mul;
const extern binary_operation_type div;
const extern binary_operation_type exp;
const extern binary_operation_type mod;

const extern unary_operation_type abs;
const extern unary_operation_type fac;

const extern binary_function_type log;

const extern function_type ln;
const extern function_type sin;
const extern function_type cos;
const extern function_type tan;
const extern function_type floor;
const extern function_type ceil;

}; // namespace brose