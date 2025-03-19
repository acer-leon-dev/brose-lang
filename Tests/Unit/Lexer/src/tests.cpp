#include "pch.hpp"

#include <brose/lexer.hpp>
#include <Boost/regex.hpp>

using enum brose::TokenType;

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
    
std::string token_to_string(const brose::Token& token)
{
    return "{" + token.value + ", " + brose::Token::typeToString(token.type) + "}";
}

std::string token_vector_to_string(const std::vector<brose::Token>& vector) 
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

bool RunUnitTest(const std::string& input, const std::vector<brose::Token>& expected, bool log = true)
{
    total_tests++;
    std::vector<brose::Token> actual = brose::Lexer::tokenize(input);
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
            { variable, "a" }, { op_equal, "=" }, { number, "2" }, { op_caret, "^" }, { number, "3" }, { op_minus, "-" },
            { function_generic, "floor" }, { op_open_paren, "(" }, { number, "3.50" }, { op_close_paren, ")" }, { eol, "\n" }, { variable, "b" },
            { op_equal, "=" }, { number, "0.333" }, { op_star, "*" }, { variable, "a" }, { op_open_paren, "(" }, { number, "5" },
            { op_minus, "-" }, { number, "1.2" }, { op_close_paren, ")" }, { eol, "\n" }, { variable, "c" }, { op_equal, "=" },
            { number, "4" }, { op_slash, "/" }, { number, "3" }, { op_plus, "+" }, { number, ".5" }, { variable, "x" },
            { eol, "\n" }, { variable, "d" }, { op_equal, "=" }, { variable, "c" }, { op_mod, "mod" }, { number, "4" },
            { op_minus, "-" }, { number, "2" }, { eol, "\n" }, { variable, "y" }, { op_equal, "=" }, { variable, "d" },
            { op_caret, "^" }, { op_open_paren, "(" }, { number, "1" }, { op_slash, "/" }, { number, "3" }, { op_close_paren, ")" },
            { op_star, "*" }, { variable, "b" }
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
            { variable, "f" }, { op_equal, "=" }, { function_logarithm, "log10" }, { op_open_paren, "(" }, { variable, "x" }, { op_caret, "^" },
            { number, "2" }, { op_close_paren, ")" }, { eol, "\n" }, { variable, "p" }, { op_equal, "=" }, { op_open_paren, "(" },
            { number, "3.14159" }, { op_close_paren, ")" }, { op_caret, "^" }, { number, "2" }, { eol, "\n" }, { variable, "m" },
            { op_equal, "=" }, { variable, "f" }, { variable, "p" }, { eol, "\n" }, { variable, "c" }, { op_equal, "=" },
            { number, "54.23" }, { op_slash, "/" }, { number, "11.96" }, { eol, "\n" }, { variable, "y" }, { op_equal, "=" },
            { variable, "m" }, { op_plus, "+" }, { op_minus, "-" }, { variable, "x" }, { op_slash, "/" }, { number, "10" },
            { op_star, "*" }, { variable, "c" }
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
            { variable, "A" }, { op_equal, "=" }, { function_generic, "ceil" }, { op_open_paren, "(" }, { number, ".5" }, { op_star, "*" },
            { variable, "x" }, { op_close_paren, ")" }, { op_star, "*" }, { number, "0.2" }, { eol, "\n" }, { variable, "a" },
            { op_equal, "=" }, { variable, "x" }, { op_star, "*" }, { op_open_paren, "(" }, { number, "1" }, { op_slash, "/" },
            { number, "3" }, { op_close_paren, ")" }, { eol, "\n" }, { variable, "B" }, { op_equal, "=" }, { function_generic, "sin" },
            { op_open_paren, "(" }, { variable, "A" }, { op_star, "*" }, { number, "66.666" }, { op_close_paren, ")" }, { eol, "\n" },
            { variable, "b" }, { op_equal, "=" }, { variable, "a" }, { variable, "B" }, { eol, "\n" }, { variable, "y" },
            { op_equal, "=" }, { variable, "b" }
        }
    );

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << successful_tests << "/" << total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";

}