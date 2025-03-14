#include "mathcompiler/Lexer.hpp"

namespace
{

bool myisspace(char c) 
{
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}

};

bool iskeyword_log(std::string token)
{
    if (!token.starts_with("log")) {
        return false;
    }

    for (char ch : token.substr(4)) {
        if (!std::isdigit(ch) && ch != '.') {
            return false;
        }
    }

    return true;
}

std::size_t getToken(const std::string& src, std::size_t pos, Token& dest)
{
    using enum TokenType;

    std::size_t start = pos;
    std::string tok;
    TokenType t;
    char lastch = src[start];
    while (std::isspace(lastch)) {
        lastch = src[++pos];
    }

    if (std::isalpha(lastch))
    {
        tok.push_back(lastch);
        for (lastch = src[++pos]; std::isalnum(lastch) || lastch == '.'; lastch = src[++pos]) {
            tok.push_back(lastch);
        }

        if (tok == "mod") {
            t = MOD;
        } else if (tok == "floor") {
            t =  GENERIC_FUNC;
        } else if (tok == "ceil") {
            t = GENERIC_FUNC;
        } else if (iskeyword_log(tok)) {
            t = LOG;
        }
    }

    // if (tok.starts_with("log"))
    
    dest = { t, tok };
    return pos - start;
}

std::vector<Token> tokenize(const std::string& src)
{
    std::vector<Token> tokens_list;
    for (std::size_t i = 0; i < src.size(); i++)
    {
        Token tok;
        i += getToken(src, i, tok);
        tokens_list.push_back(tok);
    }

    return tokens_list;
}