#include "pch.hpp"
#include <brose/Lexer.hpp>

using namespace brose;

namespace
{    

// using regex_handler = std::function<Token(const std::string& regex, const std::string& token)>;

// regex_handler create_default_value_regex_handler(const std::string& value, TokenType token_type) {
//     return [value, token_type](auto, auto){ return Token{ value, token_type}; };
// }

// regex_handler create_regex_spitting_regex_handler(TokenType token_type) {
//     return [token_type](auto regex, auto token) -> Token { 
//         return { boost::regex_match(regex), token_type};
//     };
// }

// static const std::vector<std::tuple<std::string, regex_handler>> regex_to_token_helper_map { 
//     { R"(\/\/[^\n\r]*\n)", 
//         create_default_value_regex_handler("", TokenType::None) },

//     { R"(\n)", create_default_value_regex_handler("\n",  TokenType::EOL) },
//     { R"(\()", create_default_value_regex_handler("(",   TokenType::Token_OpenParen) },
//     { R"(\))", create_default_value_regex_handler(")",   TokenType::Token_CloseParen) },
//     { R"(\|)", create_default_value_regex_handler("|",   TokenType::Absolute), },
//     { R"(=)",  create_default_value_regex_handler("=",   TokenType::Assign) },
//     { R"(\+)", create_default_value_regex_handler("+",   TokenType::Token_Plus) },
//     { R"(\-)", create_default_value_regex_handler("-",   TokenType::Token_Minus) },
//     { R"(\*)", create_default_value_regex_handler("*",   TokenType::Token_Multiply) },
//     { R"(\/)", create_default_value_regex_handler("/",   TokenType::Token_Divide) },
//     { R"(\^)", create_default_value_regex_handler("^",   TokenType::Token_Exponent) },
//     { R"(\!)", create_default_value_regex_handler("!",   TokenType::Factorial) },
//     { R"(mod)",create_default_value_regex_handler("mod", TokenType::Token_Modulus) },

//     { R"(sin|cos|tan|ln|floor|ceil)", 
//         create_regex_spitting_regex_handler(TokenType::Token_NormalFunction), },
//     { R"(log\d*\.?\d*)",              
//         create_regex_spitting_regex_handler(TokenType::LogarithmicFunction), },
//     { R"([[:alpha:]](_\d)?)",         
//         create_regex_spitting_regex_handler(TokenType::Variable), },
//     { R"(\d*\.?\d+|\d+\.?\d*)",       
//         create_regex_spitting_regex_handler(TokenType::Number) }
// };

const boost::regex SINGLE_LINE_COMMENT_PATTERN  { R"(\/\/[^\n\r]*\n)" };
const boost::regex END_OF_LINE_PATTERN          { R"(\n)" };
const boost::regex OPERATOR_PATTERN             { R"(\(|\)|=|\+|\-|\*|\/|\^|\||!|mod)" };
const boost::regex NORMAL_FUNCTION_PATTERN      { R"(sin|cos|tan|ln|floor|ceil)" };
const boost::regex LOGARITHM_PATTERN            { R"(log\d*\.?\d*)" };
const boost::regex VARIABLE_PATTERN             { R"([[:alpha:]](_\d)?)" };
const boost::regex NUMBER_PATTERN               { R"(\d*\.?\d+|\d+\.?\d*)" };

TokenType operator_string_to_token_type(const std::string& str) {
    using enum TokenType;
    
    static const std::unordered_map<std::string, TokenType> keywords { 
        { "\n",  token_eol },
        { "(",   token_open_paren },
        { ")",   token_close_paren },
        { "|",   token_absolute, },
        { "=",   token_assign },
        { "+",   token_plus },
        { "-",   token_minus },
        { "*",   token_multiply },
        { "/",   token_divide },
        { "^",   token_exponent },
        { "!",   token_factorial },
        { "mod", token_modulus }    
    };

    auto it = keywords.find(str);
    return (it == keywords.end()) ? token_none : it->second;
}

TokenType string_to_token_type(const std::string& str) {
    using enum TokenType;
    
    if      (boost::regex_match(str, SINGLE_LINE_COMMENT_PATTERN))          return token_none;
    else if (boost::regex_match(str, END_OF_LINE_PATTERN))                  return token_eol;
    else if (boost::regex_match(str, OPERATOR_PATTERN))                     return operator_string_to_token_type(str);
    else if (boost::regex_match(str, NORMAL_FUNCTION_PATTERN))              return token_normal_function;
    else if (boost::regex_match(str, LOGARITHM_PATTERN))                    return token_logarithmic_function;
    else if (boost::regex_match(str, VARIABLE_PATTERN))                     return token_variable;
    else if (boost::regex_match(str, NUMBER_PATTERN))                       return token_number;
    else                                                                    return token_none;
}

std::string initialize_lexer_regex_pattern() {
    static std::vector<std::string> pattern_list {
        { SINGLE_LINE_COMMENT_PATTERN.str() },
        { END_OF_LINE_PATTERN.str() },
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

bool Token::valid() {
    return token_type_is_valid(type) && !value.empty();
}

bool Token::equals(const Token& other) {
    return *this == other;
}

bool token_type_is_valid(TokenType type) {
    return token_type_to_int(type) & token_type_to_int(token_any);
}

int token_type_to_int(TokenType token_type) {
    return static_cast<int>(token_type);
}

std::string token_type_to_string(TokenType token_type) {
    using enum ::brose::TokenType;

    switch (token_type) {
    default: return "none";
    case token_any:         return "any";
    case token_eol:         return "end_of_line";
    case token_variable:    return "variable";
    case token_number:      return "number";
    case token_open_paren:  return "open_paren";
    case token_close_paren: return "close_paren";
    case token_assign:      return "assign";
    case token_plus:        return "plus";
    case token_minus:       return "minus";
    case token_multiply:    return "multiply";
    case token_divide:      return "divide";
    case token_exponent:    return "exponent";
    case token_modulus:     return "modulus";
    case token_absolute:    return "absolute";
    case token_factorial:   return "factorial";
    case token_normal_function:        return "normal_function";
    case token_logarithmic_function:   return "logarithmic_function";
    case token_trigonometric_function: return "trigonometric_function";
    }
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
        bool match_success = boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags | boost::match_continuous);
        if (match_success) {
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

            token_value = std::string(start_it, next_it);
            if (token_value.empty()) {
                continue;
            }
            
            start_it = next_it;

        }

        // Indentify TokenType from value and convert it to a Token object
        TokenType token_type = string_to_token_type(token_value);
        if (token_type_is_valid(token_type)) {
            tokens.emplace_back(token_value, token_type);
        }
    }
        
    return tokens;
}

}; // namespace brose
