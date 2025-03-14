#include "mathcompiler/Lexer.hpp"

namespace
{

struct mctype
{
    static bool isspace(char c) 
    {
        return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
    }

    static bool isfloatdigit(char c)
    {
        return std::isdigit(c) || c == '.';
    }

    static bool isalnumfloat(char c)
    {
        return std::isalnum(c) || c == '.';
    }
    
}; // struct mctype

struct iskeyword
{
    static bool islog(std::string tok)
    {
        // return if natural log
        if (tok == "ln") {
            return true;
        }
        
        if (!tok.starts_with("log")) {
            return false;
        }

        // verify base
        for (int i = 4; i < tok.length(); i++) {
            if (!mctype::isfloatdigit(tok[i])) {
                    return false;
            }
        }
    
        return true;
    }

}; // struct iskeyword

std::size_t getToken(const std::string& src, std::size_t pos, Token& dest)
{
    using enum TokenType;
    std::size_t start = pos;
    
    char lastch = src[start];
    
    // skip whitespace
    while (mctype::isspace(lastch)) {
        lastch = src[++pos];
    }

    std::string tok;
    TokenType t;

    // Process identifiers and keywords
    if (std::isalpha(lastch))
    {
        tok.push_back(lastch);
        for (lastch = src[++pos]; std::isalnum(lastch); lastch = src[++pos]) {
            tok.push_back(lastch);
        }

        if (tok == "mod") {
            t = MOD;
        } else if (tok == "floor") {
            t = GENERIC_FUNC;
        } else if (tok == "ceil") {
            t = GENERIC_FUNC;
        } else if (iskeyword::islog(tok)) {
            t = LOG;
        } else {
            t = IDENTIFIER;
        }

        // Match operators
        if (tok.length() == 1)
        {
            switch (tok[0]) {
                case '+': t = 0; break;
                case '-': t = 0; break;
                case '*': t = 0; break;
                case '/': t = 0; break;
                case '^': t = 0; break;
            }
        }
    }

    // Process numbers
    if (mctype::isfloatdigit(lastch))
    {
        t = NUMBER;
        do {
            tok.push_back(lastch);
            lastch = src[++pos];
        } while (mctype::isfloatdigit(lastch));
    }

    // Process comments
    if (lastch == '/')
    {
        lastch = src[++pos];
        if (lastch == '/')
        {
            do {
                lastch = src[++pos];
            } while (pos < src.length() && lastch != '\n' && lastch != '\r');
        }
    }
    
    dest = { t, tok };
    return pos - start;
} // std::size_t getToken

}; // [anonymous] namespace

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
} // std::vector<Token> tokenize
