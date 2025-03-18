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
    return type != TokenType::NOT_A_TOKEN && !value.empty();
}

namespace
{

TokenType get_keyword_type(const std::string& token)
{
    using TokenMap = std::unordered_map<std::string, TokenType>; 
    static const TokenMap keywords { 
        { "mod", TokenType::MOD } 
    };

    TokenMap::const_iterator res = keywords.find(token);
    return (res == keywords.end()) ? TokenType::NOT_A_TOKEN : res->second;
}

TokenType get_operator_type(char op)
{
    using OperatorTokenMap = std::unordered_map<char, TokenType>;
    static const OperatorTokenMap operators {
        { '\n', TokenType::ENDOFLINE },
        { '(',  TokenType::OPEN_PAREN },
        { ')',  TokenType::CLOSE_PAREN },
        { '=',  TokenType::EQUAL },
        { '+',  TokenType::PLUS },
        { '-',  TokenType::MINUS },
        { '*',  TokenType::MULTIPLY },
        { '/',  TokenType::DIVIDE },
        { '^',  TokenType::EXPONENT },
        { '|',  TokenType::ABS }
    };

    OperatorTokenMap::const_iterator res = operators.find(op);
    return (res == operators.end()) ? TokenType::NOT_A_TOKEN : res->second;
}

Token match_variable(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{ 
    std::string match = regex::match_start(R"([[:alpha:]])", src, pos, n);
    if (!match.empty()) {
        return { TokenType::VARIABLE, match };
    }

    return {};
}

Token match_token_keyword(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{ 
    static const std::array<std::string, 1> keywords { "mod" };
    static const std::string regex = 
        "\\b(" + 
        regex::join_regex_or(keywords.cbegin(), keywords.cend())
        + ")\\b";
    std::string match = regex::match_start(regex, src, pos, n);
    return { get_keyword_type(match), match };
}

Token match_token_number(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{ 
    std::string match = regex::match_start(R"(\d*\.?\d+|\d+\.?\d*)", src, pos, n);
    if (!match.empty()) {
        return { TokenType::NUMBER, match };
    }

    return {};
}

Token match_token_logarithm(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{
    std::string match = regex::match_start(R"(\b(ln|(log((\d*)(\.?)(\d*))))\b)", src, pos, n);
    if (!match.empty()) {
        return { TokenType::LOGARITHM_FUNCTION, match };
    }

    return {};
}

Token match_token_genericfunction(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{
    static const std::array<std::string, 5> list { "sin", "cos", "tan", "floor", "ceil" };
    static const std::string regex = regex::join_regex_or(list.cbegin(), list.cend());
    std::string match = regex::match_start(regex, src, pos, n);
    if (!match.empty()) {
        return { TokenType::GENERIC_FUNCTION, match };
    }

    return {};
}

Token match_token_operator(const std::string& src, std::size_t pos = 0, std::size_t n = std::string::npos)
{ 
    static const std::string regex = R"(\n|\(|\)|=|\+|\-|\*|\/|\^|\|)";
    std::string match = regex::match_start(regex, src, pos, n);
    return { get_operator_type(match[0]), match };
}

Token get_next_token(const std::string& src, std::size_t* p_pos)
{
    std::size_t& pos = *p_pos;
    char lastch = src[pos];
    
    // Skip leading whitespace
    while (isspacenn(lastch)) {
        pos++;
        lastch = src[pos];
    }
    
    Token token;

    // Check if at end of source
    if  (pos >= src.length()) {
        return token;
    }
    
    if (std::isalpha(lastch))
    {
        if      (token = match_token_keyword(src, pos))         {}
        else if (token = match_token_genericfunction(src, pos)) {}
        else if (token = match_token_logarithm(src, pos))       {}
        else if (token = match_variable(src, pos))              {}
    }
    else if (isdigitf(lastch)) {
        token = match_token_number(src, pos);
    }
    else if (src.substr(pos, 2) == "//") {   
        token.value = regex::match_start(R"(\/\/[^\n\r]*)", src, pos);
        pos++;
    }
    else
    {
        token = match_token_operator(src, pos);
        if (!token) {
            throw std::logic_error(std::format("\'{}\' is not a valid operator", lastch));
        }
    }
    
    pos += token.value.length() - 1;
    return token;
} // getToken

}; // {anonymous} namespace

std::vector<Token> tokenizeSource(const std::string& src)
{
    // std::vector<Token> tokens;
    // for (std::size_t i = 0; i < src.size(); i++)
    // {
    //     Token tok = get_next_token(src, &i);
    //     if (tok) {
    //         tokens_list.push_back(tok);
    //     }
    // }
    
    // return tokens_list;

    // 1. Keywords, Keyworded Functions, Variables
    // 2. Numbers
    // 3. Single-line comments
    // 4. Operators
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
                type = GENERIC_FUNCTION;
            }
            // * Logarithmic function syntax i.e., ln, logN
            else if (match = regex::match_start(R"(\b(ln|(log((\d*)(\.?)(\d*))))\b)", src, pos);
                !match.empty()) {
                type = LOGARITHM_FUNCTION;
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
        
        if (type != NOT_A_TOKEN) {
            tokens.emplace_back(type, match);
        }
        pos += match.length() - 1;
    }
        
    return tokens;
} // tokenizeSource