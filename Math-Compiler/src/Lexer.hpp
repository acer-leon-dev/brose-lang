#include "PCH.hpp"

enum class TokenType
{
    ENDOFFILE,

    IDENTIFIER,
    NUMBER,

    OPEN_PAREN,
    CLOSE_PAREN,
    NEWLINE,

    EQUAL,
    PLUS,
    DASH,
    STAR,
    SLASH,
    CARET,
    
    MOD,
    LOG,
    TRIG_FUNCTION
};

struct Token
{
    TokenType type;
    std::string value;
};


bool isspace_but_not_newline(char c) 
{
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}
std::string getToken(std::string::iterator it)
{
    std::string tok;

    for (; isspace_but_not_newline(*it); it++)


    return it;
}

std::vector<std::string> tokenize(std::string source)
{
    std::vector<std::string> value;
    std::string curr_token;
    for (char ch : source)
    {
        if (isspace_but_not_newline(ch))
        {
            if (!curr_token.empty()) {
                value.push_back(curr_token);

            }
        }
        else
        {

        }
    }

    return value;
}