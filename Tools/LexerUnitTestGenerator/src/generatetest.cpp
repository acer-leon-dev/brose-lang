#include "pch.hpp"

#include <brose/lexer.hpp>

std::string generate_brose_script()
{
    std::string script;
}

std::string token_to_string(const brose::Token& token)
{
    return "{" + brose::Token::token_type_to_string(token.type)  + ", " + token.val + "}";
}

std::string tokenize_script_and_format_tokens(const std::string& source)
{
    std::vector<brose::Token> tokens = brose::Lexer::tokenize(source);
    std::string result;
    for (std::size_t i = 0; i < tokens.size(); i++)
    {
        result += token_to_string(tokens[i]);
        if (i < tokens.size() - 1) {
            result += ", ";
        }
        
        if (i % 3 == 2) {
            result += "\n";
        }
    }
}

std::string generate_test_code()
{
    std::string code;
    std::string script = generate_brose_script();
    code += "RunUnitTest(\n";
    code += script + "\n";
    code += tokenize_script_and_format_tokens(script);
    code += ")";
}

int main(int argc, char** argv)
{
    std::size_t count = 1;
    if (argc == 2)
    {
        try 
        {
            count = std::stoul(argv[1]);
        }
        catch (std::invalid_argument e) 
        {
            std::cerr << "Error: " << e.what() << "\n";
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        std::cout <<generate_test_code() << "\n\n";
    }
}