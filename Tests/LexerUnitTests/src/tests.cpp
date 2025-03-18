#include "Brose/Lexer.hpp"
#include "Boost/regex.hpp"
using enum TokenType;

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

class UnitTest
{
public:
    const std::string test_name;
    const std::string input;
    std::vector<Token> expected;
    static inline std::size_t successful_tests = 0;
    static inline std::size_t total_tests = 0;

    UnitTest(const std::string& test_name, const std::string& input, const std::vector<Token>& expected_output)
    :   test_name { test_name },
        input { input },
        expected { expected_output }
    {
    }

    bool run_test(bool output = true)
    {
        total_tests++;
        std::vector<Token> actual = Lexer::tokenize(input);
        // bool passed = std::OP_equal(actual.begin(), actual.end(), expected.begin(), actual.end());
        bool passed = actual == expected;

        std::cout << "!------------------------------------------------!\n";
        // if (passed) {
        //     successful_tests++;
        //     std::cout << "Test \"" << test_name << "\": SUCCESS!\n";
        //     std::cout << "Output:\n\t";
        //     print_tokens(actual);
        //     std::cout << "\n";
        // }
        // else {
        //     std::cout << "Test \"" << test_name << "\": FAIL!\n";
            
        //     std::cout << "Expected output:\n\t";
        //     print_tokens(expected);
        //     std::cout << "\n";
            
        //     std::cout << "Incorrect output:\n\t";
        //     print_tokens(actual);
        //     std::cout << "\n";
        // }

        if (!output)
        {
            if (passed)
            {
                successful_tests++;
                return passed;
            }
        }
        
        if (passed) {
            successful_tests++;
            std::cout << "Test \"" << test_name << "\": SUCCESS!\n";
        }
        else {
            std::cout << "Test \"" << test_name << "\": FAIL!\n";    
        }

        std::cout << "Expected output:\n\t";
        print_tokens(expected);
        std::cout << "\n";
        
        std::cout << "Actual output:\n\t";
        print_tokens(actual);
        std::cout << "\n";

        std::cout << "!------------------------------------------------!\n";
        std::cout << "\n";

        return passed;
    }

private:
    void print_tokens(const std::vector<Token>& vector) 
    {
        // std::cout << "{ ";
        for (std::size_t i = 0; i < vector.size() - 1; i++) {
            std::cout << decontrol(vector[i].value) << " ";
        }
        std::cout << vector.back().value;
        // std::cout << " }";
    }
};

int main()
{;
    UnitTest test1 {
        "1",
        "// EXAMPLE1.brose\n"
        "a = 2^3 - floor(3.50)\n"
        "b = 0.333 * a(5 - 1.2)\n"
        "c = 4 / 3 + .5x\n"
        "d = c mod 4 - 2\n"
        "y = d ^ ( 1/3 ) * b",
        {
            { VARIABLE, "a" }, { OP_EQUAL, "=" }, { NUMBER, "2" },
            { OP_EXPONENT, "^" }, { NUMBER, "3" }, { OP_MINUS, "-" },
            { FUNCTION_GENERIC, "floor" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "3.50" },
            { OP_CLOSE_PAREN, ")" }, { ENDOFLINE, "\n" }, { VARIABLE, "b" },
            { OP_EQUAL, "=" }, { NUMBER, "0.333" }, { OP_MULTIPLY, "*" },
            { VARIABLE, "a" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "5" },
            { OP_MINUS, "-" }, { NUMBER, "1.2" }, { OP_CLOSE_PAREN, ")" },
            { ENDOFLINE, "\n" }, { VARIABLE, "c" }, { OP_EQUAL, "=" },
            { NUMBER, "4" }, { OP_DIVIDE, "/" }, { NUMBER, "3" },
            { OP_PLUS, "+" }, { NUMBER, ".5" }, { VARIABLE, "x" },
            { ENDOFLINE, "\n" }, { VARIABLE, "d" }, { OP_EQUAL, "=" },
            { VARIABLE, "c" }, { OP_MOD, "mod" }, { NUMBER, "4" },
            { OP_MINUS, "-" }, { NUMBER, "2" }, { ENDOFLINE, "\n" },
            { VARIABLE, "y" }, { OP_EQUAL, "=" }, { VARIABLE, "d" },
            { OP_EXPONENT, "^" }, { OP_OPEN_PAREN, "(" }, { NUMBER, "1" },
            { OP_DIVIDE, "/" }, { NUMBER, "3" }, { OP_CLOSE_PAREN, ")" },
            { OP_MULTIPLY, "*" }, { VARIABLE, "b" }
        }
    };
    test1.run_test();

    UnitTest test2 {
        "2",
        "// EXAMPLE2.brose\n"
        "f = log10(x^2)\n"
        "p = (3.14159)^2\n"
        "m = fp\n"
        "c = 54.23/11.96\n"
        "y = m + -x / 10 * c",
        {
            { VARIABLE, "f" }, { OP_EQUAL, "=" }, { FUNCTION_LOGARITHM, "log10" },
            { OP_OPEN_PAREN, "(" }, { VARIABLE, "x" }, { OP_EXPONENT, "^" },
            { NUMBER, "2" }, { OP_CLOSE_PAREN, ")" }, { ENDOFLINE, "\n" },
            { VARIABLE, "p" }, { OP_EQUAL, "=" }, { OP_OPEN_PAREN, "(" },
            { NUMBER, "3.14159" }, { OP_CLOSE_PAREN, ")" }, { OP_EXPONENT, "^" },
            { NUMBER, "2" }, { ENDOFLINE, "\n" }, { VARIABLE, "m" },
            { OP_EQUAL, "=" }, { VARIABLE, "f" }, { VARIABLE, "p" },
            { ENDOFLINE, "\n" }, { VARIABLE, "c" }, { OP_EQUAL, "=" },
            { NUMBER, "54.23" }, { OP_DIVIDE, "/" }, { NUMBER, "11.96" },
            { ENDOFLINE, "\n" }, { VARIABLE, "y" }, { OP_EQUAL, "=" },
            { VARIABLE, "m" }, { OP_PLUS, "+" }, { OP_MINUS, "-" },
            { VARIABLE, "x" }, { OP_DIVIDE, "/" }, { NUMBER, "10" },
            { OP_MULTIPLY, "*" }, { VARIABLE, "c" }
        }
    };
    test2.run_test();

    UnitTest test3 {
        "3",
        "// EXAMPLE3.brose\n"
        "A = ceil(.5*x) * 0.2\n"
        "a = x * (1 / 3)\n"
        "B = sin(A * 66.666)\n"
        "b = aB\n"
        "y = b",
        {
            { VARIABLE, "A" }, { OP_EQUAL, "=" }, { FUNCTION_GENERIC, "ceil" },
            { OP_OPEN_PAREN, "(" }, { NUMBER, ".5" }, { OP_MULTIPLY, "*" },
            { VARIABLE, "x" }, { OP_CLOSE_PAREN, ")" }, { OP_MULTIPLY, "*" },
            { NUMBER, "0.2" }, { ENDOFLINE, "\n" }, { VARIABLE, "a" },
            { OP_EQUAL, "=" }, { VARIABLE, "x" }, { OP_MULTIPLY, "*" },
            { OP_OPEN_PAREN, "(" }, { NUMBER, "1" }, { OP_DIVIDE, "/" },
            { NUMBER, "3" }, { OP_CLOSE_PAREN, ")" }, { ENDOFLINE, "\n" },
            { VARIABLE, "B" }, { OP_EQUAL, "=" }, { FUNCTION_GENERIC, "sin" },
            { OP_OPEN_PAREN, "(" }, { VARIABLE, "A" }, { OP_MULTIPLY, "*" },
            { NUMBER, "66.666" }, { OP_CLOSE_PAREN, ")" }, { ENDOFLINE, "\n" },
            { VARIABLE, "b" }, { OP_EQUAL, "=" }, { VARIABLE, "a" },
            { VARIABLE, "B" }, { ENDOFLINE, "\n" }, { VARIABLE, "y" },
            { OP_EQUAL, "=" }, { VARIABLE, "b" }
        }
    };
    test3.run_test();

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << UnitTest::successful_tests << "/" << UnitTest::total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";

}