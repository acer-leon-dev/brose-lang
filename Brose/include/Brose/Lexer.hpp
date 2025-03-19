#pragma once
#include "PCH.hpp"

enum class TokenType : int
{
    NOT_A_TOKEN = 0x0,
    EOL = 0x1,
    VARIABLE = 0x2,
    NUMBER = 0x4,
    OP_OPEN_PAREN = 0x8,
    OP_CLOSE_PAREN = 0x10,
    OP_ABS = 0x20,
    OP_EQUAL = 0x40,
    OP_PLUS = 0x80,
    OP_MINUS = 0x100,
    OP_MULTIPLY = 0x200,
    OP_DIVIDE = 0x400,
    OP_EXPONENT = 0x800,
    OP_FACTORIAL = 0x1000,
    OP_MOD = 0x2000,
    FUNCTION_GENERIC = 0x4000,
    FUNCTION_LOGARITHM = 0x8000
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