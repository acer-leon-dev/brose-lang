#pragma once
#include "PCH.hpp"

enum class TokenType : int
{
    NOT_A_TOKEN = 0,
    ENDOFLINE,
    VARIABLE,
    NUMBER,
    OP_OPEN_PAREN,
    OP_CLOSE_PAREN,
    OP_ABS,
    OP_EQUAL,
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_EXPONENT,
    OP_FACTORIAL,
    OP_MOD,
    FUNCTION_GENERIC,
    FUNCTION_LOGARITHM
};

struct Token
{
    TokenType type;
    std::string value;

    Token();
    Token(TokenType type, const std::string& value);
    operator bool();
    bool operator<=>(const Token &) const = default;
    static std::string typeToString(TokenType t);
};

class Lexer
{
public:
    static std::vector<Token> tokenize(const std::string& src); 
    const std::vector<Token>& getTokens();
private:
    std::vector<Token> tokens;
};