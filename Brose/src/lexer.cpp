#include "pch.hpp"
#include <brose/Lexer.hpp>

using namespace brose;

namespace {

struct token_info {
public:
    token_info(const std::string& pattern, TokenType type) : m_pattern{pattern}, m_type{type} {

    }
    
    TokenType get_type_if_match(const std::string& s) const {
        return (boost::regex_match(s, m_pattern)) ? m_type : token_none;
    }

    const boost::regex& regex() const {
        return m_pattern;
    }

    std::string pattern() const {
        return m_pattern.str();
    }

    TokenType type() const {
        return m_type;
    }

private:
    boost::regex    m_pattern;
    TokenType       m_type;
    // std::string result; 
};

struct lexer {
public:
    lexer(const std::string& source);
    const std::vector<Token>& tokens();
private:
    std::string m_source;
    std::size_t m_position;
    std::vector<Token> m_tokens;
    static const std::array<token_info, 17>
        m_token_info_list;
    
    void m_create_token_vector();
    std::optional<Token> m_get_next_token();
    void m_skip_specific_whitespace();
    static std::optional<std::string> m_find_match_at_begin(const token_info& info, const std::string& text, std::size_t begin);
};

lexer::lexer(const std::string& source) 
:   m_source{source},
    m_position{0}
{
    m_create_token_vector();
}

const std::vector<Token>& lexer::tokens() {
    return m_tokens;
}

void lexer::m_create_token_vector() {
    for (auto opt_token = m_get_next_token(); opt_token; opt_token = m_get_next_token()) {
        if (opt_token) {
            if (opt_token->type & token_flag_any) {
                std::cerr << "Added \"" << opt_token->value << "\"\n";
                m_tokens.push_back(*opt_token);
            }
        } else {
            std::cerr << "This is probably erroneous\n";
        }
    }
}

std::optional<Token> lexer::m_get_next_token(){
    if (m_position >= m_source.size()) {
        return {};
    }

    // Skip whitespace
    m_skip_specific_whitespace();

    // Iterate through each token_info object to determine there is a token at the current position
    for (const token_info& info : m_token_info_list) {
        if (auto opt_str = m_find_match_at_begin(info, m_source, m_position)) {
            std::cerr << "found a match, creating token\n";
            m_position += opt_str->length();
            return std::make_optional<Token>(*opt_str, info.type());
        }
    }
    // Return empty if token isn't found
    return {};
}

void lexer::m_skip_specific_whitespace() {
    // Skip whitespace
    while (m_source.at(m_position) == ' ') {
        std::cerr << "skipped a space\n";
        m_position++;
    }
}

std::optional<std::string> lexer::m_find_match_at_begin(const token_info& info, const std::string& text, std::size_t begin) {
    if (begin >= text.length()) {
        return {};
    }
    
    boost::smatch match;
    boost::regex_search(text.cbegin() + begin, text.cend(), match, info.regex());
    if (match[0].matched) {
        return match[0].str();
    } else {
        return {};
    }
}

const std::array<token_info, 17> lexer::m_token_info_list {
    // None-matches
    token_info{ R"(\/\/[^\n\r]*\n)", token_none },

    // Operators
    token_info{ R"(\n)",    token_eol },
    token_info{ R"(\()",    token_open_paren },
    token_info{ R"(\))",    token_close_paren },
    token_info{ R"(\|)",    token_absolute },
    token_info{ R"(=)",     token_assign },
    token_info{ R"(\+)",    token_plus },
    token_info{ R"(\-)",    token_minus },
    token_info{ R"(\*)",    token_multiply },
    token_info{ R"(\/)",    token_divide },
    token_info{ R"(\^)",    token_exponent },
    token_info{ R"(\!)",    token_factorial },
    token_info{ R"(mod)",   token_modulus },
    // Functions
    token_info{ R"(sin|cos|tan|ln|floor|ceil)", token_normal_function },
    token_info{ R"(log\d*\.?\d*)", token_logarithmic_function },
    // Variables
    token_info{ R"([[:alpha:]](_\d)?)", token_variable },
    // Number literals
    token_info{ R"(\d*\.?\d+|\d+\.?\d*)", token_number }
};

static const std::vector<token_info> token_info_list { 
    token_info{ R"(\/\/[^\n\r]*\n)", token_none },
    token_info{ R"(\n)", token_eol },
    token_info{ R"(\()", token_open_paren },
    token_info{ R"(\))", token_close_paren },
    token_info{ R"(\|)", token_absolute },
    token_info{ R"(=)", token_assign },
    token_info{ R"(\+)", token_plus },
    token_info{ R"(\-)", token_minus },
    token_info{ R"(\*)", token_multiply },
    token_info{ R"(\/)", token_divide },
    token_info{ R"(\^)", token_exponent },
    token_info{ R"(\!)", token_factorial },
    token_info{ R"(mod)", token_modulus },
    token_info{ R"(sin|cos|tan|ln|floor|ceil)", token_normal_function },
    token_info{ R"(log\d*\.?\d*)", token_logarithmic_function },
    token_info{ R"([[:alpha:]](_\d)?)", token_variable },
    token_info{ R"(\d*\.?\d+|\d+\.?\d*)", token_number }
};

const boost::regex SINGLE_LINE_COMMENT_PATTERN  { R"(\/\/[^\n\r]*\n)" };
const boost::regex END_OF_LINE_PATTERN          { R"(\n)" };
const boost::regex OPERATOR_PATTERN             { R"(\(|\)|=|\+|\-|\*|\/|\^|\||!|mod)" };
const boost::regex NORMAL_FUNCTION_PATTERN      { R"(sin|cos|tan|ln|floor|ceil)" };
const boost::regex LOGARITHM_PATTERN            { R"(log\d*\.?\d*)" };
const boost::regex VARIABLE_PATTERN             { R"([[:alpha:]](_\d)?)" };
const boost::regex NUMBER_PATTERN               { R"(\d*\.?\d+|\d+\.?\d*)" };

TokenType operator_string_to_token_type(const std::string& str) {
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
    return (it == keywords.end()) ? token_flag_none : it->second;
}

// TokenType string_to_token_type(const std::string& s) {
//     for (const token_info& info : token_info_list) {
//         if (info.get_type_if_match(s) & token_flag_any) {
//             return info.type;
//         }
//     }

//     return token_flag_none;
// }

// std::string initialize_lexer_regex_pattern() {
//     // static std::vector<std::string> pattern_list {
//     //     { SINGLE_LINE_COMMENT_PATTERN.str() },
//     //     { END_OF_LINE_PATTERN.str() },
//     //     { OPERATOR_PATTERN.str() },
//     //     { NORMAL_FUNCTION_PATTERN.str() },
//     //     { LOGARITHM_PATTERN.str() },
//     //     { VARIABLE_PATTERN.str() },
//     //     { NUMBER_PATTERN.str() }
//     // };

//     std::vector<std::string> pattern_list;
//     for (const token_info& info : token_info_list) {
//         if (info.type & token_flag_any) {
//             pattern_list.push_back('(' + info.pattern() + ')');
//             break;
//         }
//     }

//     return boost::algorithm::join(pattern_list, "|");
// }

}; // {anonymous} namespace

namespace brose {

bool Token::valid() {
    return type & token_flag_any && !value.empty();
}

std::string token_type_to_string(TokenType token_type) {
    switch (token_type) {
    default:                return "none";
    case token_flag_any:    return "any";
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
    case token_normal_function:
        return "normal_function";
    case token_logarithmic_function:
        return "logarithmic_function";
    case token_trigonometric_function:
        return "trigonometric_function";
    }
}

std::vector<Token> lex(const std::string& src) {
    lexer l{src};
    return l.tokens();
    // // Configure regex for Brose's lexer
    // static const std::string lexer_pattern = initialize_lexer_regex_pattern();
    // static const boost::regex pattern { lexer_pattern };
    // static const auto match_flags = boost::match_not_null;
    // // Tokenize source using a regex-based string splitting algorithm
    // std::vector<Token> tokens;
    // auto start_it = src.cbegin();
    // while (start_it < src.cend()) {
    //     // auto token = lexer::get_first_match();
    //     boost::smatch this_match;
    //     std::string token_value;
    //     bool match_success = boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags | boost::match_continuous);
    //     if (match_success) {
    //         token_value = this_match[0];
    //         start_it += this_match[0].str().size();
    //     } else {
    //         std::string::const_iterator next_it;

    //         if (!boost::regex_search(start_it, src.cend(), this_match, pattern, match_flags)) {
    //             next_it = src.end();
    //         } else {
    //             next_it = start_it + this_match.position();
    //         }

    //         token_value = std::string(start_it, next_it);
    //         if (token_value.empty()) {
    //             continue;
    //         }
            
    //         start_it = next_it;
    //     }

    //     // Indentify TokenType from value and convert it to a Token object
    //     TokenType token_type = string_to_token_type(token_value);
    //     if (token_type != token_flag_none) {
    //         tokens.emplace_back(token_value, token_type);
    //     }
    // }
        
    // return tokens;
}

}; // namespace brose
