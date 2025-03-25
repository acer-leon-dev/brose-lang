#pragma once

#include <string>
#include <vector>

namespace brose 
{

enum class TokenType : int
{
    EOL          = 1 << 0,
    Variable     = 1 << 1,
    Number       = 1 << 2,

    OpenParen    = 1 << 3,
    CloseParen   = 1 << 4,
    
    Assign       = 1 << 5,
    Plus         = 1 << 6,
    Minus        = 1 << 7,
    Multiply     = 1 << 8,
    Divide       = 1 << 9,
    Exponent     = 1 << 10,
    Modulus      = 1 << 11,

    Absolute     = 1 << 12,
    Factorial    = 1 << 13,
    
    NormalFunction           = 1 << 14,
    LogarithmicFunction      = 1 << 15,
    TrigonometricFunction    = 1 << 16,

    None    = 0,
    Any     = EOL | Variable | Number | OpenParen 
            | CloseParen | Assign | Plus | Minus 
            | Multiply | Divide | Exponent | Modulus 
            | Absolute | Factorial | NormalFunction 
            | LogarithmicFunction | TrigonometricFunction
};

struct Token
{
    std::string value = "";
    TokenType type = TokenType::None;
    
    bool valid();
    bool equals(const Token& other);
    bool operator==(const Token& other) const = default; 
};

bool token_type_is_valid(TokenType type);

int token_type_to_int(TokenType type);

std::string token_type_to_string(TokenType type);

std::vector<Token> lex(const std::string& src); 

}; // namespace brose
