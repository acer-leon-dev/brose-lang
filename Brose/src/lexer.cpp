#include "pch.hpp"
#include <brose/lexer.hpp>
#include <brose/ctype.hpp>
#include <brose/regex.hpp>

namespace brose 
{

Token::Token()
:   type { TokenType::none }
{

}

Token::Token(TokenType type, const std::string& value)
:   type { type },
    value { value }
{

}

Token::operator bool()
{
    return static_cast<bool>(type) && !value.empty();
}

std::string Token::typeToString(TokenType type)
{
    using enum TokenType;
    
    switch (type) {
        case none: return "none";
        case eol: return "eol";
        case variable: return "variable";
        case number: return "number";
        case op_open_paren: return "op_open_paren";
        case op_close_paren: return "op_close_paren";
        case op_abs: return "op_abs";
        case op_equal: return "op_equal";
        case op_plus: return "op_plus";
        case op_minus: return "op_minus";
        case op_star: return "op_star";
        case op_slash: return "op_slash";
        case op_caret: return "op_caret";
        case op_factorial: return "op_factorial";
        case op_mod: return "op_mod";
        case function_generic: return "function_generic";
        case function_logarithm: return "function_logarithm";
        case function_trig: return "function_trig";

        case op_binary: return "op_binary";
        case op_unary: return "op_unary";
        case op_any: return "op_any";
        // case function_binary: return "function_binary";
        case function_unary: return "function_unary";
        case function_any: return "function_any";
    }   

    return "";
}

namespace
{

TokenType get_keyword_type(const std::string& token)
{
    using TokenMap = std::unordered_map<std::string, TokenType>; 
    static const TokenMap keywords { 
        { "mod", TokenType::op_mod } 
    };

    TokenMap::const_iterator res = keywords.find(token);
    return (res == keywords.end()) ? TokenType::none : res->second;
}

TokenType get_operator_type(char op)
{
    using OperatorTokenMap = std::unordered_map<char, TokenType>;
    static const OperatorTokenMap operators {
        { '\n', TokenType::eol },
        { '(',  TokenType::op_open_paren },
        { ')',  TokenType::op_close_paren },
        { '|',  TokenType::op_abs },
        { '=',  TokenType::op_equal },
        { '+',  TokenType::op_plus },
        { '-',  TokenType::op_minus },
        { '*',  TokenType::op_star },
        { '/',  TokenType::op_slash },
        { '^',  TokenType::op_caret },
        { '!',  TokenType::op_factorial }
    };

    OperatorTokenMap::const_iterator res = operators.find(op);
    return (res == operators.end()) ? TokenType::none : res->second;
}

}; // {anonymous} namespace

std::vector<Token> Lexer::tokenize(const std::string& src)
{
    using enum TokenType;
    std::vector<Token> tokens;

    for (std::size_t pos = 0; pos < src.size(); pos++)
    {
        char lastch = src[pos];

        // Skip leading whitespace
        while (isspacenn(lastch)) {
            pos++;
            lastch = src[pos];
        }

        std::string match;
        TokenType type;
        if (std::isalpha(lastch)) {
            // * Multi-character/Keyword operators
            if (match = regex::match_start(R"(\b(mod)\b)", src, pos);
                !match.empty()) {
                type = get_keyword_type(match);
            }
            // * Generic functions (regular functions with one parameter)
            else if (match = regex::match_start(R"(sin|cos|tan|floor|ceil)", src, pos);
                !match.empty()) {
                type = function_generic;
            }
            // * Logarithmic function syntax i.e., ln, logN
            else if (match = regex::match_start(R"(\b(ln|(log_?\d*\.?\d*))\b)", src, pos);
                !match.empty()) {
                type = function_logarithm;
            }
            // * One-letter variables
            else if (match = regex::match_start(R"([[:alpha:]](_\d)?)", src, pos);
                !match.empty()) {
                type = variable;
            }
            else {
                
            }
        }
        // * Floating-point numbers
        else if (isdigitf(lastch)) {
            match = regex::match_start(R"(\d*\.?\d+|\d+\.?\d*)", src, pos);
            type = number;
        }
        // * Single-line comments
        else if (src.substr(pos, 2) == "//") {
            match = regex::match_start(R"(\/\/[^\n\r]*)", src, pos);
            type = none;
            pos++;
        }
        // Single-character operators
        else {
            match = regex::match_start(R"(\n|\(|\)|=|\+|\-|\*|\/|\^|\||!)", src, pos);
            type = get_operator_type(match[0]);
        }
        
        if (static_cast<bool>(type)) {
            tokens.emplace_back(type, match);
        }
        pos += match.length() - 1;
    }
        
    return tokens;
} 

const std::vector<Token>& Lexer::getTokens()
{
    return tokens;
}

}; // namespace brose