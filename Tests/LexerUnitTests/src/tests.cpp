#include "Brose/Lexer.hpp"
#include "Boost/regex.hpp"
using enum TokenType;

namespace
{

std::string decontrol(std::string str)
{   
    // static boost::regex r_sqte { R"(\')" };
    // static boost::regex r_dqte { R"(\")" };
    // static boost::regex r_ques { R"(\?)" };
    // static boost::regex r_bsla { R"(\\)" };
    // static boost::regex r_bell { R"(\a)" };
    // static boost::regex r_back { R"(\b)" };
    // static boost::regex r_fmfd { R"(\f)" };
    // static boost::regex r_vtab { R"(\v)" };
    static boost::regex r_lnfd { R"(\n)" };
    static boost::regex r_cret { R"(\r)" };
    static boost::regex r_htab { R"(\t)" };
    
    // str = boost::regex_replace(str, r_sqte, R"(\\')");
    // str = boost::regex_replace(str, r_dqte, R"(\\")");
    // str = boost::regex_replace(str, r_ques, R"(\\?)");
    // str = boost::regex_replace(str, r_bsla, R"(\\\)");
    // str = boost::regex_replace(str, r_bell, R"(\\a)");
    // str = boost::regex_replace(str, r_back, R"(\\t)");
    // str = boost::regex_replace(str, r_fmfd, R"(\\b)");
    // str = boost::regex_replace(str, r_vtab, R"(\\v)");
    str = boost::regex_replace(str, r_lnfd, R"(\\n)");
    str = boost::regex_replace(str, r_cret, R"(\\n)");
    str = boost::regex_replace(str, r_htab, R"(\\n)");

    return str;
}
    
std::string token_to_string(const Token& token)
{
    return "{" + token.value + ", " + Token::typeToString(token.type) + "}";
}

std::string token_vector_to_string(const std::vector<Token>& vector) 
{
    std::string str;
    // str += "{ ";
    for (std::size_t i = 0; i < vector.size() - 1; i++) {
        str += decontrol(vector[i].value) + " ";
    }
    str += vector.back().value;
    // str += " }";
    return str;
}

inline std::size_t successful_tests = 0;
inline std::size_t total_tests = 0;

bool RunUnitTest(const std::string& input, const std::vector<Token>& expected, bool log = true)
{
    total_tests++;
    std::vector<Token> actual = Lexer::tokenize(input);
    bool passed = actual == expected;

    if (!log)
    {
        if (passed) {
            successful_tests++;
        }
        return passed;
    }
    
    std::cout << "!------------------------------------------------!\n";
    if (passed) {
        successful_tests++;
        std::cout << "Test " << total_tests << ": SUCCESS!\n";
        std::cout << "Output:\n\t" << token_vector_to_string(actual) << "\n";
    }
    else {
        std::cout << "Test " << total_tests << ": FAIL!\n";
        std::cout << "Expected output:\n\t" << token_vector_to_string(expected) << "\n";
        std::cout << "Incorrect output:\n\t" << token_vector_to_string(actual) << "\n";
    }

    std::cout << "!------------------------------------------------!\n";
    std::cout << "\n";
    return passed;
}

};

int main()
{;
    RunUnitTest(
        "// ex1.brose\n"
        "a = 2^3 - floor(3.50)\n"
        "b = 0.333 * a(5 - 1.2)\n"
        "c = 4 / 3 + .5x\n"
        "d = c mod 4 - 2\n"
        "y = d ^ ( 1/3 ) * b",
        {
            { VARIABLE, "a" }, { OP_EQUAL, "=" }, { NUMBER, "2" }, { OP_EXPONENT, "^" }, { NUMBER, "3" }, { OP_MINUS, "-" },
            { FUNCTION_GENERIC, "floor" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "3.50" }, { OP_CLOSE_PAREN, ")" }, { EOL, "\n" }, { VARIABLE, "b" },
            { OP_EQUAL, "=" }, { NUMBER, "0.333" }, { OP_MULTIPLY, "*" }, { VARIABLE, "a" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "5" },
            { OP_MINUS, "-" }, { NUMBER, "1.2" }, { OP_CLOSE_PAREN, ")" }, { EOL, "\n" }, { VARIABLE, "c" }, { OP_EQUAL, "=" },
            { NUMBER, "4" }, { OP_DIVIDE, "/" }, { NUMBER, "3" }, { OP_PLUS, "+" }, { NUMBER, ".5" }, { VARIABLE, "x" },
            { EOL, "\n" }, { VARIABLE, "d" }, { OP_EQUAL, "=" }, { VARIABLE, "c" }, { OP_MOD, "mod" }, { NUMBER, "4" },
            { OP_MINUS, "-" }, { NUMBER, "2" }, { EOL, "\n" }, { VARIABLE, "y" }, { OP_EQUAL, "=" }, { VARIABLE, "d" },
            { OP_EXPONENT, "^" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "1" }, { OP_DIVIDE, "/" }, { NUMBER, "3" }, { OP_CLOSE_PAREN, ")" },
            { OP_MULTIPLY, "*" }, { VARIABLE, "b" }
        }
    );

    RunUnitTest(
        "// ex2.brose\n"
        "f = log10(x^2)\n"
        "p = (3.14159)^2\n"
        "m = fp\n"
        "c = 54.23/11.96\n"
        "y = m + -x / 10 * c",
        {
            { VARIABLE, "f" }, { OP_EQUAL, "=" }, { FUNCTION_LOGARITHM, "log10" }, { OP_OPEN_PAREN, "(" }, { VARIABLE, "x" }, { OP_EXPONENT, "^" },
            { NUMBER, "2" }, { OP_CLOSE_PAREN, ")" }, { EOL, "\n" }, { VARIABLE, "p" }, { OP_EQUAL, "=" }, { OP_OPEN_PAREN, "(" },
            { NUMBER, "3.14159" }, { OP_CLOSE_PAREN, ")" }, { OP_EXPONENT, "^" }, { NUMBER, "2" }, { EOL, "\n" }, { VARIABLE, "m" },
            { OP_EQUAL, "=" }, { VARIABLE, "f" }, { VARIABLE, "p" }, { EOL, "\n" }, { VARIABLE, "c" }, { OP_EQUAL, "=" },
            { NUMBER, "54.23" }, { OP_DIVIDE, "/" }, { NUMBER, "11.96" }, { EOL, "\n" }, { VARIABLE, "y" }, { OP_EQUAL, "=" },
            { VARIABLE, "m" }, { OP_PLUS, "+" }, { OP_MINUS, "-" }, { VARIABLE, "x" }, { OP_DIVIDE, "/" }, { NUMBER, "10" },
            { OP_MULTIPLY, "*" }, { VARIABLE, "c" }
        }
    );

    RunUnitTest(
        "// ex3.brose\n"
        "A = ceil(.5*x) * 0.2\n"
        "a = x * (1 / 3)\n"
        "B = sin(A * 66.666)\n"
        "b = aB\n"
        "y = b",
        {
            { VARIABLE, "A" }, { OP_EQUAL, "=" }, { FUNCTION_GENERIC, "ceil" }, { OP_OPEN_PAREN, "(" }, { NUMBER, ".5" }, { OP_MULTIPLY, "*" },
            { VARIABLE, "x" }, { OP_CLOSE_PAREN, ")" }, { OP_MULTIPLY, "*" }, { NUMBER, "0.2" }, { EOL, "\n" }, { VARIABLE, "a" },
            { OP_EQUAL, "=" }, { VARIABLE, "x" }, { OP_MULTIPLY, "*" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "1" }, { OP_DIVIDE, "/" },
            { NUMBER, "3" }, { OP_CLOSE_PAREN, ")" }, { EOL, "\n" }, { VARIABLE, "B" }, { OP_EQUAL, "=" }, { FUNCTION_GENERIC, "sin" },
            { OP_OPEN_PAREN, "(" }, { VARIABLE, "A" }, { OP_MULTIPLY, "*" }, { NUMBER, "66.666" }, { OP_CLOSE_PAREN, ")" }, { EOL, "\n" },
            { VARIABLE, "b" }, { OP_EQUAL, "=" }, { VARIABLE, "a" }, { VARIABLE, "B" }, { EOL, "\n" }, { VARIABLE, "y" },
            { OP_EQUAL, "=" }, { VARIABLE, "b" }
        }
    );

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << successful_tests << "/" << total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";

}