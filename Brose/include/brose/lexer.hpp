#pragma once

#include <string>
#include <vector>

namespace brose 
{

enum TokenType : int
{
    TT_EOL          = 1 << 0,
    TT_Variable     = 1 << 1,
    TT_Number       = 1 << 2,

    TT_OpenParen    = 1 << 3,
    TT_CloseParen   = 1 << 4,
    
    TT_Assign       = 1 << 5,
    TT_Plus         = 1 << 6,
    TT_Minus        = 1 << 7,
    TT_Multiply     = 1 << 8,
    TT_Divide       = 1 << 9,
    TT_Exponent     = 1 << 10,
    TT_Modulus      = 1 << 11,

    TT_Absolute     = 1 << 12,
    TT_Factorial    = 1 << 13,
    
    TT_NormalFunction           = 1 << 14,
    TT_LogarithmicFunction      = 1 << 15,
    TT_TrigonometricFunction    = 1 << 16,
    
    TT_Parenthesis      = TT_OpenParen | TT_CloseParen,
    TT_BinaryOperator   = TT_Plus | TT_Minus | TT_Multiply | TT_Divide | TT_Exponent | TT_Modulus,
    TT_UnaryOperator    = TT_Absolute | TT_Factorial,
    TT_AnyOperator      = TT_BinaryOperator | TT_UnaryOperator | TT_Parenthesis,

    TT_BinaryFunction   = TT_LogarithmicFunction,
    TT_UnaryFunction    = TT_NormalFunction | TT_TrigonometricFunction,
    TT_AnyFunction      = TT_BinaryFunction | TT_UnaryFunction,
    
    TT_None = 0,
    TT_Any  = TT_EOL | TT_Variable | TT_Number | TT_Parenthesis | TT_AnyOperator | TT_AnyFunction 
};

struct Token
{
    TokenType type = TT_None;
    std::string value = "";
    
    operator bool();

    bool operator==(const Token& other) const = default; 
};

std::string token_type_to_string(TokenType t);

std::vector<Token> lex(const std::string& src); 

}; // namespace brose
