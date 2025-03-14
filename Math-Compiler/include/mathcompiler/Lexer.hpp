#pragma once
#include "../PCH.hpp"

enum class TokenType : int
{
    ENDOFFILE = 0,

    IDENTIFIER,
    NUMBER,

    OPEN_PAREN,
    CLOSE_PAREN,
    NEWLINE,

    EQUAL,
    PLUS,
    DASH,
    STAR,
    SLASH,
    CARET,
    
    MOD,
    LOG,
    GENERIC_FUNC
};

struct Token
{
    TokenType type;
    std::string value;
};

std::size_t getToken(const std::string& src, std::size_t pos, Token& dest);
std::vector<Token> tokenize(const std::string& src);