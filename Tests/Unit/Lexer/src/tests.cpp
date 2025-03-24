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
    return "{" + token.value + ", " + brose::token_type_to_string(token.type) + "}";
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
    std::vector<brose::Token> actual = brose::lex(input);
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
            { TT_Variable, "a" }, { TT_Assign, "=" }, { TT_Number, "2" }, { TT_Exponent, "^" }, { TT_Number, "3" }, { TT_Minus, "-" },
            { TT_NormalFunction, "floor" }, { TT_OpenParen, "(" }, { TT_Number, "3.50" }, { TT_CloseParen, ")" }, { TT_EOL, "\n" }, { TT_Variable, "b" },
            { TT_Assign, "=" }, { TT_Number, "0.333" }, { TT_Multiply, "*" }, { TT_Variable, "a" }, { TT_OpenParen, "(" }, { TT_Number, "5" },
            { TT_Minus, "-" }, { TT_Number, "1.2" }, { TT_CloseParen, ")" }, { TT_EOL, "\n" }, { TT_Variable, "c" }, { TT_Assign, "=" },
            { TT_Number, "4" }, { TT_Divide, "/" }, { TT_Number, "3" }, { TT_Plus, "+" }, { TT_Number, ".5" }, { TT_Variable, "x" },
            { TT_EOL, "\n" }, { TT_Variable, "d" }, { TT_Assign, "=" }, { TT_Variable, "c" }, { TT_Modulus, "mod" }, { TT_Number, "4" },
            { TT_Minus, "-" }, { TT_Number, "2" }, { TT_EOL, "\n" }, { TT_Variable, "y" }, { TT_Assign, "=" }, { TT_Variable, "d" },
            { TT_Exponent, "^" }, { TT_OpenParen, "(" }, { TT_Number, "1" }, { TT_Divide, "/" }, { TT_Number, "3" }, { TT_CloseParen, ")" },
            { TT_Multiply, "*" }, { TT_Variable, "b" }
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
            { TT_Variable, "f" }, { TT_Assign, "=" }, { TT_LogarithmicFunction, "log10" }, { TT_OpenParen, "(" }, { TT_Variable, "x" }, { TT_Exponent, "^" },
            { TT_Number, "2" }, { TT_CloseParen, ")" }, { TT_EOL, "\n" }, { TT_Variable, "p" }, { TT_Assign, "=" }, { TT_OpenParen, "(" },
            { TT_Number, "3.14159" }, { TT_CloseParen, ")" }, { TT_Exponent, "^" }, { TT_Number, "2" }, { TT_EOL, "\n" }, { TT_Variable, "m" },
            { TT_Assign, "=" }, { TT_Variable, "f" }, { TT_Variable, "p" }, { TT_EOL, "\n" }, { TT_Variable, "c" }, { TT_Assign, "=" },
            { TT_Number, "54.23" }, { TT_Divide, "/" }, { TT_Number, "11.96" }, { TT_EOL, "\n" }, { TT_Variable, "y" }, { TT_Assign, "=" },
            { TT_Variable, "m" }, { TT_Plus, "+" }, { TT_Minus, "-" }, { TT_Variable, "x" }, { TT_Divide, "/" }, { TT_Number, "10" },
            { TT_Multiply, "*" }, { TT_Variable, "c" }
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
            { TT_Variable, "A" }, { TT_Assign, "=" }, { TT_NormalFunction, "ceil" }, { TT_OpenParen, "(" }, { TT_Number, ".5" }, { TT_Multiply, "*" },
            { TT_Variable, "x" }, { TT_CloseParen, ")" }, { TT_Multiply, "*" }, { TT_Number, "0.2" }, { TT_EOL, "\n" }, { TT_Variable, "a" },
            { TT_Assign, "=" }, { TT_Variable, "x" }, { TT_Multiply, "*" }, { TT_OpenParen, "(" }, { TT_Number, "1" }, { TT_Divide, "/" },
            { TT_Number, "3" }, { TT_CloseParen, ")" }, { TT_EOL, "\n" }, { TT_Variable, "B" }, { TT_Assign, "=" }, { TT_NormalFunction, "sin" },
            { TT_OpenParen, "(" }, { TT_Variable, "A" }, { TT_Multiply, "*" }, { TT_Number, "66.666" }, { TT_CloseParen, ")" }, { TT_EOL, "\n" },
            { TT_Variable, "b" }, { TT_Assign, "=" }, { TT_Variable, "a" }, { TT_Variable, "B" }, { TT_EOL, "\n" }, { TT_Variable, "y" },
            { TT_Assign, "=" }, { TT_Variable, "b" }
        }
    );

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << successful_tests << "/" << total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";

}