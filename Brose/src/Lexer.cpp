#include "Brose/Lexer.hpp"
#include "Extendedctype.hpp"
#include "Regex.hpp"


Token::Token()
:   type { TokenType::NOT_A_TOKEN }
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
        case NOT_A_TOKEN: return "NOT_A_TOKEN";
        case EOL: return "EOL";
        case VARIABLE: return "VARIABLE";
        case NUMBER: return "NUMBER";
        case OP_OPEN_PAREN: return "OP_OP_OPEN_PAREN";
        case OP_CLOSE_PAREN: return "OP_OP_CLOSE_PAREN";
        case OP_ABS: return "OP_ABS";
        case OP_EQUAL: return "OP_EQUAL";
        case OP_PLUS: return "OP_PLUS";
        case OP_MINUS: return "OP_MINUS";
        case OP_MULTIPLY: return "OP_MULTIPLY";
        case OP_DIVIDE: return "OP_DIVIDE";
        case OP_EXPONENT: return "OP_EXPONENT";
        case OP_FACTORIAL: return "OP_FACTORIAL";
        case OP_MOD: return "OP_MOD";
        case FUNCTION_GENERIC: return "FUNCTION_GENERIC";
        case FUNCTION_LOGARITHM: return "FUNCTION_LOGARITHM";
    }   

    return "";
}

namespace
{

TokenType get_keyword_type(const std::string& token)
{
    using TokenMap = std::unordered_map<std::string, TokenType>; 
    static const TokenMap keywords { 
        { "mod", TokenType::OP_MOD } 
    };

    TokenMap::const_iterator res = keywords.find(token);
    return (res == keywords.end()) ? TokenType::NOT_A_TOKEN : res->second;
}

TokenType get_operator_type(char op)
{
    using OperatorTokenMap = std::unordered_map<char, TokenType>;
    static const OperatorTokenMap operators {
        { '\n', TokenType::EOL },
        { '(',  TokenType::OP_OPEN_PAREN },
        { ')',  TokenType::OP_CLOSE_PAREN },
        { '=',  TokenType::OP_EQUAL },
        { '+',  TokenType::OP_PLUS },
        { '-',  TokenType::OP_MINUS },
        { '*',  TokenType::OP_MULTIPLY },
        { '/',  TokenType::OP_DIVIDE },
        { '^',  TokenType::OP_EXPONENT },
        { '|',  TokenType::OP_ABS }
    };

    OperatorTokenMap::const_iterator res = operators.find(op);
    return (res == operators.end()) ? TokenType::NOT_A_TOKEN : res->second;
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
                type = FUNCTION_GENERIC;
            }
            // * Logarithmic function syntax i.e., ln, logN
            else if (match = regex::match_start(R"(\b(ln|(log((\d*)(\.?)(\d*))))\b)", src, pos);
                !match.empty()) {
                type = FUNCTION_LOGARITHM;
            }
            // * One-letter variables
            else if (match = regex::match_start(R"([[:alpha:]])", src, pos);
                !match.empty()) {
                type = VARIABLE;
            }
        }
        // * Floating-point numbers
        else if (isdigitf(lastch)) {
            match = regex::match_start(R"(\d*\.?\d+|\d+\.?\d*)", src, pos);
            type = NUMBER;
        }
        // * Single-line comments
        else if (src.substr(pos, 2) == "//") {
            match = regex::match_start(R"(\/\/[^\n\r]*)", src, pos);
            type = NOT_A_TOKEN;
            pos++;
        }
        // Single-character operators
        else {
            match = regex::match_start(R"(\n|\(|\)|=|\+|\-|\*|\/|\^|\|)", src, pos);
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