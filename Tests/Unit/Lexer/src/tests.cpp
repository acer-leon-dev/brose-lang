#include "pch.hpp"

#include "util.hpp"
#include <brose/lexer.hpp>

using enum brose::TokenType;

namespace
{

void testLexerProducesCorrectTokenSequenceFromScript1() {
    const static std::string script =
        "// ex1.brose\na = 2^3 - floor(3.50)\n"
        "b = 0.333 * a(5 - 1.2)\n"
        "c = 4 / 3 + .5x\n"
        "d = c mod 4 - 2\n"
        "y = d ^ ( 1/3 ) * b";

    const static std::vector<brose::Token> expected {
        {"a",     token_variable},
        {"=",     token_operator_assign},
        {"2",     token_literal_number},
        {"^",     token_operator_exponent},
        {"3",     token_literal_number},
        {"-",     token_operator_minus},
        {"floor", token_function_normal},
        {"(",     token_operator_open_paren},
        {"3.50",  token_literal_number},
        {")",     token_operator_close_paren},
        {"\n",    token_eol},
        {"b",     token_variable},
        {"=",     token_operator_assign},
        {"0.333", token_literal_number},
        {"*",     token_operator_multiply},
        {"a",     token_variable},
        {"(",     token_operator_open_paren},
        {"5",     token_literal_number},
        {"-",     token_operator_minus},
        {"1.2",   token_literal_number},
        {")",     token_operator_close_paren},
        {"\n",    token_eol},
        {"c",     token_variable},
        {"=",     token_operator_assign},
        {"4",     token_literal_number},
        {"/",     token_operator_divide},
        {"3",     token_literal_number},
        {"+",     token_operator_plus},
        {".5",    token_literal_number},
        {"x",     token_variable},
        {"\n",    token_eol},
        {"d",     token_variable},
        {"=",     token_operator_assign},
        {"c",     token_variable},
        {"mod",   token_operator_modulus},
        {"4",     token_literal_number},
        {"-",     token_operator_minus},
        {"2",     token_literal_number},
        {"\n",    token_eol},
        {"y",     token_variable},
        {"=",     token_operator_assign},
        {"d",     token_variable},
        {"^",     token_operator_exponent},
        {"(",     token_operator_open_paren},
        {"1",     token_literal_number},
        {"/",     token_operator_divide},
        {"3",     token_literal_number},
        {")",     token_operator_close_paren},
        {"*",     token_operator_multiply},
        {"b",     token_variable}
    };

    assertTokenListsAreEqual(brose::tokenize_source(script), expected);
}


void testLexerProducesCorrectTokenSequenceFromScript2() {
    const static std::string script = 
        "// ex2.brose\n"
        "f = log10(x^2)\n"
        "p = (3.14159)^2\n"
        "m = fp\n"
        "c = 54.23/11.96\n"
        "y = m + -x / 10 * c";

    const static std::vector<brose::Token> expected {
        {"f",       token_variable},
        {"=",       token_operator_assign},
        {"log10",   token_function_logarithmic},
        {"(",       token_operator_open_paren},
        {"x",       token_variable},
        {"^",       token_operator_exponent},
        {"2",       token_literal_number},
        {")",       token_operator_close_paren},
        {"\n",      token_eol},
        {"p",       token_variable},
        {"=",       token_operator_assign},
        {"(",       token_operator_open_paren},
        {"3.14159", token_literal_number},
        {")",       token_operator_close_paren},
        {"^",       token_operator_exponent},
        {"2",       token_literal_number},
        {"\n",      token_eol},
        {"m",       token_variable},
        {"=",       token_operator_assign},
        {"f",       token_variable},
        {"p",       token_variable},
        {"\n",      token_eol},
        {"c",       token_variable},
        {"=",       token_operator_assign},
        {"54.23",   token_literal_number},
        {"/",       token_operator_divide},
        {"11.96",   token_literal_number},
        {"\n",      token_eol},
        {"y",       token_variable},
        {"=",       token_operator_assign},
        {"m",       token_variable},
        {"+",       token_operator_plus},
        {"-",       token_operator_minus},
        {"x",       token_variable},
        {"/",       token_operator_divide},
        {"10",      token_literal_number},
        {"*",       token_operator_multiply},
        {"c",       token_variable}
    };

    assertTokenListsAreEqual(brose::tokenize_source(script), expected);
}


void testLexerProducesCorrectTokenSequenceFromScript3() {
    const static std::string script = 
        "// ex3.brose\n"
        "A = ceil(.5*x) * 0.2\n"
        "a = x * (1 / 3)\n"
        "B = sin(A * 66.666)\n"
        "b = aB\n"
        "y = b";

    const static std::vector<brose::Token> expected {
        {"A",       token_variable},
        {"=",       token_operator_assign},
        {"ceil",    token_function_normal},
        {"(",       token_operator_open_paren},
        {".5",      token_literal_number},
        {"*",       token_operator_multiply},
        {"x",       token_variable},
        {")",       token_operator_close_paren},
        {"*",       token_operator_multiply},
        {"0.2",     token_literal_number},
        {"\n",      token_eol},
        {"a",       token_variable},
        {"=",       token_operator_assign},
        {"x",       token_variable},
        {"*",       token_operator_multiply},
        {"(",       token_operator_open_paren},
        {"1",       token_literal_number},
        {"/",       token_operator_divide},
        {"3",       token_literal_number},
        {")",       token_operator_close_paren},
        {"\n",      token_eol},
        {"B",       token_variable},
        {"=",       token_operator_assign},
        {"sin",     token_function_normal},
        {"(",       token_operator_open_paren},
        {"A",       token_variable},
        {"*",       token_operator_multiply},
        {"66.666",  token_literal_number},
        {")",       token_operator_close_paren},
        {"\n",      token_eol},
        {"b",       token_variable},
        {"=",       token_operator_assign},
        {"a",       token_variable},
        {"B",       token_variable},
        {"\n",      token_eol},
        {"y",       token_variable},
        {"=",       token_operator_assign},
        {"b",       token_variable}
    };

    assertTokenListsAreEqual(brose::tokenize_source(script), expected);
}

};

int main()
{;
    testLexerProducesCorrectTokenSequenceFromScript1();
    testLexerProducesCorrectTokenSequenceFromScript2();
    testLexerProducesCorrectTokenSequenceFromScript3();

    std::cout << "!------------------------------------------------!\n";
    std::cout << "# Successful tests: " << successful_tests << "/" << total_tests << " tests\n";
    std::cout << "!------------------------------------------------!\n";
}