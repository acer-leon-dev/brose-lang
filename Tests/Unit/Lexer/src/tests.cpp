#include "pch.hpp"

#include "util.hpp"
#include <brose/lexer.hpp>

using enum brose::TokenType;

namespace
{

void test_lexer_produces_correct_token_sequence_from_script() {
    const static std::string script =
    "// ex1.brose\na = 2^3 - floor(3.50)\n"
    "b = 0.333 * a(5 - 1.2)\n"
    "c = 4 / 3 + .5x\n"
    "d = c mod 4 - 2\n"
    "y = d ^ ( 1/3 ) * b";

    const static std::vector<brose::Token> expected {
        {"a",     Variable},
        {"=",     Assign},
        {"2",     Number},
        {"^",     Exponent},
        {"3",     Number},
        {"-",     Minus},
        {"floor", NormalFunction},
        {"(",     OpenParen},
        {"3.50",  Number},
        {")",     CloseParen},
        {"\n",    EOL},
        {"b",     Variable},
        {"=",     Assign},
        {"0.333", Number},
        {"*",     Multiply},
        {"a",     Variable},
        {"(",     OpenParen},
        {"5",     Number},
        {"-",     Minus},
        {"1.2",   Number},
        {")",     CloseParen},
        {"\n",    EOL},
        {"c",     Variable},
        {"=",     Assign},
        {"4",     Number},
        {"/",     Divide},
        {"3",     Number},
        {"+",     Plus},
        {".5",    Number},
        {"x",     Variable},
        {"\n",    EOL},
        {"d",     Variable},
        {"=",     Assign},
        {"c",     Variable},
        {"mod",   Modulus},
        {"4",     Number},
        {"-",     Minus},
        {"2",     Number},
        {"\n",    EOL},
        {"y",     Variable},
        {"=",     Assign},
        {"d",     Variable},
        {"^",     Exponent},
        {"(",     OpenParen},
        {"1",     Number},
        {"/",     Divide},
        {"3",     Number},
        {")",     CloseParen},
        {"*",     Multiply},
        {"b",     Variable}
    };

    assertTokenListsAreEqual(brose::lex(script), expected);
}

};

int main()
{;
    test_lexer_produces_correct_token_sequence_from_script();

    // test_lexer_produces_correct_token_sequence_from_script(
    //     "// ex2.brose\nf = log10(x^2)\np = (3.14159)^2\nm = fp\nc = 54.23/11.96\ny = m + -x / 10 * c",
    //     {
    //         { "f", Variable }, { "=", Assign }, { "log10", LogarithmicFunction },
    //         { "(", OpenParen }, { "x", Variable }, { "^", Exponent },
    //         { "2", Number }, { ")", CloseParen }, { "\n", EOL },
    //         { "p", Variable }, { "=", Assign }, { "(", OpenParen },
    //         { "3.14159", Number }, { ")", CloseParen }, { "^", Exponent },
    //         { "2", Number }, { "\n", EOL }, { "m", Variable },
    //         { "=", Assign }, { "f", Variable }, { "p", Variable },
    //         { "\n", EOL }, { "c", Variable }, { "=", Assign },
    //         { "54.23", Number }, { "/", Divide }, { "11.96", Number },
    //         { "\n", EOL }, { "y", Variable }, { "=", Assign },
    //         { "m", Variable }, { "+", Plus }, { "-", Minus },
    //         { "x", Variable }, { "/", Divide }, { "10", Number },
    //         { "*", Multiply }, { "c", Variable }
    //     }
    // );

    // test_lexer_produces_correct_token_sequence_from_script(
    //     "// ex3.brose\nA = ceil(.5*x) * 0.2\na = x * (1 / 3)\nB = sin(A * 66.666)\nb = aB\ny = b",
    //     {
    //         { "A", Variable }, { "=", Assign }, { "ceil", NormalFunction },
    //         { "(", OpenParen }, { ".5", Number }, { "*", Multiply },
    //         { "x", Variable }, { ")", CloseParen }, { "*", Multiply },
    //         { "0.2", Number }, { "\n", EOL }, { "a", Variable },
    //         { "=", Assign }, { "x", Variable }, { "*", Multiply },
    //         { "(", OpenParen }, { "1", Number }, { "/", Divide },
    //         { "3", Number }, { ")", CloseParen }, { "\n", EOL },
    //         { "B", Variable }, { "=", Assign }, { "sin", NormalFunction },
    //         { "(", OpenParen }, { "A", Variable }, { "*", Multiply },
    //         { "66.666", Number }, { ")", CloseParen }, { "\n", EOL },
    //         { "b", Variable }, { "=", Assign }, { "a", Variable },
    //         { "B", Variable }, { "\n", EOL }, { "y", Variable },
    //         { "=", Assign }, { "b", Variable }
    //     }
    // );

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << successful_tests << "/" << total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";

}