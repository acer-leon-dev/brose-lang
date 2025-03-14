#include "mathcompiler/Mathcompiler.hpp"

std::string script_1 = 
R"(a = 2^3 - floor(3.50)
b = 0.333 * a(5 - 1.2)
c = 4 / 3 + .5x
d = c mod 4 - 2
y = d ^ ( 1/3 ) * b)";

std::string script_2 = 
R"(f = log10(x^2)
p = (3.14159)^2
m = fp
c = 54.23/11.96
y = m + -x / 10 * c)";

std::string script_3 = 
R"(A = ceil(.5*x) * 0.2
a = x * (1 / 3)
B = sin(A * 66.666)
b = aB
y = b)";

std::string readFile(std::filesystem::path path)
{
    std::ifstream in { path };
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int main(int argc, char ** argv)
{
    // std::string src0 = readFile(argv[1]);
    std::string src = script_1;
	std::cout << "EXAMPLE1.math\n```\n" << src << "\n```\n\n";
    auto tokens = tokenize(src);
    for (auto tok : tokens) {
        if (tok.value == "\n") {
            std::cout << "\\n" << '\n';
        } 
        else {
            std::cout << tok.value << " " << (int)tok.type << "\n";
        }
    }
}
