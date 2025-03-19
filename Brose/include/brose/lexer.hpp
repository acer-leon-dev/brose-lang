#pragma once

#include <string>
#include <vector>

namespace brose 
{

enum class TokenType : int
{
    eol                 = 1 << 0,
    variable            = 1 << 1,
    number              = 1 << 2,

    op_open_paren       = 1 << 3,
    op_close_paren      = 1 << 4,
    op_equal            = 1 << 5,
    op_plus             = 1 << 6,
    op_minus            = 1 << 7,
    op_star             = 1 << 8,
    op_slash            = 1 << 9,
    op_caret            = 1 << 10,
    op_mod              = 1 << 11,
    op_abs              = 1 << 12,
    op_factorial        = 1 << 13,
    
    function_generic    = 1 << 14,
    function_logarithm  = 1 << 15,
    function_trig       = 1 << 16,
    
    op_binary       = op_plus | op_minus | op_star | op_slash | op_caret | op_mod,
    op_unary        = op_abs | op_factorial,
    op_any          = op_binary | op_unary,
    function_binary = function_logarithm,
    function_unary  = function_generic | function_trig,
    function_any    = function_binary | function_unary,
    none            = 0,
    any             = eol | variable | number | op_any | function_any 
};

struct Token
{
    TokenType type;
    std::string value;

    Token();
    Token(TokenType type, const std::string& value);
    operator bool();
    bool operator<=>(const Token &) const         
      = default;
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

}; // namespace brose