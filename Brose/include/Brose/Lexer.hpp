#pragma once
#include "PCH.hpp"

enum class TokenType : int
{
    NOT_A_TOKEN = -1,

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
    bool operator<=>(const Token &) const = default;
};

class Lexer
{
public:
    static std::vector<Token> tokenize(const std::string& src); 
    const std::vector<Token>& getTokens();
private:
    std::vector<Token> tokens;
};