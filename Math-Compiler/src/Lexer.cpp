#include "mathcompiler/Lexer.hpp"

namespace
{

struct mctype
{
    mctype() = delete;

    static bool isSpace(char c) 
    {
        return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
    }

    static bool isDigitFloat(char c)
    {
        return std::isdigit(c) || c == '.';
    }

    static bool isAlnumFloat(char c)
    {
        return std::isalnum(c) || c == '.';
    }
    
}; // struct mctype

struct iskeyword
{
    iskeyword() = delete;

    // Verifies if `tok` is a logarithmic function
    static bool isLog(const std::string& tok)
    {
        // return if natural log
        if (tok == "ln") {
            return true;
        }
        
        if (!tok.starts_with("log")) {
            return false;
        }
    
        return true;
    }

    // Verifies if `tok` is a generic math function (has a name and one paremater)
    static bool isGenericFunc(const std::string& tok)
    {
        static std::array<std::string, 5> functions { "sin", "cos", "tan", "floor", "ceil" };

        for (std::string funcstr : functions)
        {
            if (tok == funcstr) {
                return true;
            }
        }

        return false;
    }

}; // struct iskeyword

TokenType getOperatorType(char op)
{
    using enum TokenType;

    switch (op) {
        default:
            throw;
        case '\n': 
            return NEWLINE;
        case '(': 
            return OPEN_PAREN;
        case ')': 
            return CLOSE_PAREN;
        case '=': 
            return EQUAL;
        case '+': 
            return PLUS;
        case '-': 
            return MINUS;
        case '*': 
            return MULTIPLY;
        case '/': 
            return DIVIDE;
        case '^': 
            return EXPONENT;
        case '|': 
            return ABS;
    }
}

// gets the number immediately following `pos`
std::string getNumber(const std::string& src, std::size_t& pos)
{
    std::string numstr;
    while (mctype::isDigitFloat(src[pos + 1])) {
        numstr.push_back(src[++pos]);
    }

    return numstr;
}

Token getToken(const std::string& src, std::size_t& pos)
{
    using enum TokenType;
    
    char lastch = src[pos];
    
    // skip whitespace
    while (mctype::isSpace(lastch)) {
        lastch = src[++pos];
    }

    TokenType toktype;
    std::string tokstr;

    // Process identifiers and keywords
    if (std::isalpha(lastch))
    {
        std::size_t varpos = pos;
        
        tokstr.push_back(lastch);
        while (std::isalnum(src[pos + 1])) {
            lastch = src[++pos];
            tokstr.push_back(lastch);
        }
        
        if (tokstr == "mod") 
        {
            toktype = MOD;
        }
        else if (iskeyword::isGenericFunc(tokstr)) 
        {
            toktype = GENERIC_FUNC;
        }
        else if (iskeyword::isLog(tokstr)) 
        {
            toktype = LOG;
            tokstr.append(getNumber(src, pos));
        }
        else 
        {
            toktype = VARIABLE;
            tokstr = tokstr[0];
            pos = varpos;
        }
    }

    // Process numbers
    else if (mctype::isDigitFloat(lastch))
    {
        toktype = NUMBER;
        tokstr.push_back(lastch);
        tokstr.append(getNumber(src, pos));
    }

    // Process comments
    else if (src.substr(pos, 2) == "//")
    {
        toktype = NOT_A_TOKEN; 
        
        pos += 2;
        lastch = src[pos];
        while (pos < src.length() && lastch != '\n' && lastch != '\r') {
            lastch = src[++pos];
        }
    }
    
    // Match operators
    else {
        tokstr.push_back(lastch);
        toktype = getOperatorType(lastch);
    }

    return { toktype, tokstr };
} // std::size_t getToken

}; // [anonymous] namespace

std::vector<Token> tokenizeSource(const std::string& src)
{
    std::vector<Token> tokens_list;
    for (std::size_t i = 0; i < src.size(); i++)
    {
        Token tok = getToken(src, i);
        if (!tok.value.empty()) {
            tokens_list.push_back(tok);
        }
    }
    
    return tokens_list;
} // std::vector<Token> tokenize