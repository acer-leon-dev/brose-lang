#pragma once
#include "../PCH.hpp"

enum class TokenType : int
{
    INVALID_TOKEN = -1,

    ENDOFLINE,
    
    VARIABLE,
    NUMBER,
    
    OPEN_PAREN,
    CLOSE_PAREN,
    ABS,

    EQUAL,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EXPONENT,

    FACTORIAL,
    
    MOD,
    GENERIC_FUNCTION,
    LOGARITHM_FUNCTION
};

struct Token
{
    TokenType type;
    std::string value;

    Token();
    Token(TokenType type, const std::string& value);
    operator bool();
};

std::vector<Token> tokenizeSource(const std::string& src);