#include "pch.hpp"
#include <brose/Lexer.hpp>
#include <brose/ctype.hpp>

using namespace brose;

namespace
{    

TokenType get_operator(const std::string& token) {
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

    auto it = keywords.find(token);
    return (it == keywords.end()) ? TT_None : it->second;

}

const boost::regex END_OF_LINE_PATTERN          { R"(\n)" };
const boost::regex SINGLE_LINE_COMMENT_PATTERN  { R"(\/\/[^\n\r]*)" };
const boost::regex OPERATOR_PATTERN             { R"(\(|\)|=|\+|\-|\*|\/|\^|\||!|mod)" };
const boost::regex NORMAL_FUNCTION_PATTERN      { R"(sin|cos|tan|ln|floor|ceil)" };
const boost::regex LOGARITHM_PATTERN            { R"(log\d*\.?\d*)" };
const boost::regex VARIABLE_PATTERN             { R"([[:alpha:]](_\d)?)" };
const boost::regex NUMBER_PATTERN               { R"(\d*\.?\d+|\d+\.?\d*)" };

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
    for (auto& str : pattern_list) { str = '(' + str + ')'; }
    return boost::algorithm::join(pattern_list, "|");
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

TokenType get_token_type(const std::string& str) {
    if      (is_newline(str))               return TT_EOL;
    else if (is_single_line_comment(str))   return TT_None;
    else if (is_operator(str))              return get_operator(str);
    else if (is_normal_function(str))       return TT_NormalFunction;
    else if (is_logarithm(str))             return TT_LogarithmicFunction;
    else if (is_variable(str))              return TT_Variable;
    else if (is_number(str))                return TT_Number;
    else                                    return TT_None;
}

}; // {anonymous} namespace

namespace brose {

Token::operator bool() {
    return static_cast<bool>(type) && !value.empty();
}

std::string token_type_to_string(TokenType t) {
    return "";
}

    
std::vector<Token> lex(const std::string& src) {
    static const std::string lexer_pattern = initialize_lexer_regex_pattern();
    const boost::regex pattern { lexer_pattern };
    static const auto match_flags =  boost::match_not_null;
    std::vector<std::string> token_values;
    auto start_it = src.cbegin();
    while (start_it < src.cend()) {
        boost::smatch this_match;

        if (boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags | boost::match_continuous)) {
            token_values.push_back(this_match[0]);
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

            if (auto s = std::string(start_it, next_it); !s.empty()) {
                token_values.push_back(s);
                start_it = next_it;
            }
        }
    }

    std::vector<Token> tokens;
    for (const auto& token_value : token_values) {
        TokenType type = get_token_type(token_value);
        if (type) {
            tokens.push_back(Token{type, token_value});
        }
    }
        
    return tokens;
}

}; // namespace brose