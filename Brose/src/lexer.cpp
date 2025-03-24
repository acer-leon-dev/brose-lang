#include "pch.hpp"
#include <brose/Lexer.hpp>

using namespace brose;

namespace
{    

const boost::regex END_OF_LINE_PATTERN          { R"(\n)" };
const boost::regex SINGLE_LINE_COMMENT_PATTERN  { R"(\/\/[^\n\r]*)" };
const boost::regex OPERATOR_PATTERN             { R"(\(|\)|=|\+|\-|\*|\/|\^|\||!|mod)" };
const boost::regex NORMAL_FUNCTION_PATTERN      { R"(sin|cos|tan|ln|floor|ceil)" };
const boost::regex LOGARITHM_PATTERN            { R"(log\d*\.?\d*)" };
const boost::regex VARIABLE_PATTERN             { R"([[:alpha:]](_\d)?)" };
const boost::regex NUMBER_PATTERN               { R"(\d*\.?\d+|\d+\.?\d*)" };

TokenType operator_str_to_token_type(const std::string& str) {
    static const std::unordered_map<std::string, TokenType> keywords { 
        { "\n", TT_EOL },
        { "(",  TT_OpenParen },
        { ")",  TT_CloseParen },
        { "|",  TT_Absolute, },
        { "=",  TT_Assign },
        { "+",  TT_Plus },
        { "-",  TT_Minus },
        { "*",  TT_Multiply },
        { "/",  TT_Divide },
        { "^",  TT_Exponent },
        { "!",  TT_Factorial },
        { "mod", TT_Modulus }    
    };

    auto it = keywords.find(str);
    return (it == keywords.end()) ? TT_None : it->second;
}

bool is_newline(const std::string& str) {
    return boost::regex_match(str, END_OF_LINE_PATTERN);
}

bool is_single_line_comment(const std::string& str) {
    return boost::regex_match(str, SINGLE_LINE_COMMENT_PATTERN);
}

bool is_operator(const std::string& str) {
    return boost::regex_match(str, OPERATOR_PATTERN);
}

bool is_normal_function(const std::string& str) {
    return boost::regex_match(str, NORMAL_FUNCTION_PATTERN);
}

bool is_logarithm(const std::string& str) {
    return boost::regex_match(str, LOGARITHM_PATTERN);
}

bool is_variable(const std::string& str) {
    return boost::regex_match(str, VARIABLE_PATTERN);
}

bool is_number(const std::string& str) {
    return boost::regex_match(str, NUMBER_PATTERN);
}

TokenType str_to_token_type(const std::string& str) {
    if      (is_newline(str))               return TT_EOL;
    else if (is_single_line_comment(str))   return TT_None;
    else if (is_operator(str))              return operator_str_to_token_type(str);
    else if (is_normal_function(str))       return TT_NormalFunction;
    else if (is_logarithm(str))             return TT_LogarithmicFunction;
    else if (is_variable(str))              return TT_Variable;
    else if (is_number(str))                return TT_Number;
    else                                    return TT_None;
}

std::string initialize_lexer_regex_pattern() {
    static std::vector<std::string> pattern_list {
        { END_OF_LINE_PATTERN.str() },
        { SINGLE_LINE_COMMENT_PATTERN.str() },
        { OPERATOR_PATTERN.str() },
        { NORMAL_FUNCTION_PATTERN.str() },
        { LOGARITHM_PATTERN.str() },
        { VARIABLE_PATTERN.str() },
        { NUMBER_PATTERN.str() }
    };
    for (auto& str : pattern_list) 
        str = '(' + str + ')';
    return boost::algorithm::join(pattern_list, "|");
}

}; // {anonymous} namespace

namespace brose {

Token::operator bool() {
    return type && !value.empty();
}

std::string token_type_to_string(TokenType t) {
    return "";
}

std::vector<Token> lex(const std::string& src) {
    // Configure regex for Brose's lexer
    static const std::string lexer_pattern = initialize_lexer_regex_pattern();
    static const boost::regex pattern { lexer_pattern };
    static const auto match_flags = boost::match_not_null;
    // Tokenize source using a regex-based string splitting algorithm
    std::vector<Token> tokens;
    auto start_it = src.cbegin();
    while (start_it < src.cend()) {
        boost::smatch this_match;
        std::string token_value;
        if (boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags | boost::match_continuous)) {
            token_value = this_match[0];
            start_it += this_match[0].str().size();
        }
        else {
            std::string::const_iterator next_it;

            if (!boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags)) {
                next_it = src.end();
            }
            else {
                next_it = start_it + this_match.position();
            }

            if (token_value = std::string(start_it, next_it); !token_value.empty()) {
                start_it = next_it;
            }
            else {
                continue;
            }

            // Indentify TokenType from value and convert it to a Token object
            TokenType token_type = str_to_token_type(token_value);
            if (token_type) {
                tokens.push_back(Token{token_type, token_value});
            }
        }
    }
        
    return tokens;
}

}; // namespace brose
