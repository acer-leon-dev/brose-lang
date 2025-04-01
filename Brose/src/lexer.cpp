#include "pch.hpp"
#include <brose/Lexer.hpp>

using namespace brose;

namespace {

struct TokenInfo {
public:
    TokenInfo(const std::string& pattern, TokenType type) : m_pattern{pattern}, m_type{type} {

    }

    const boost::regex& regex() const {
        return m_pattern;
    }

    TokenType type() const {
        return m_type;
    }

private:
    boost::regex    m_pattern;
    TokenType       m_type;
    // std::string result; 
};

TokenType operator_string_to_token_type(const std::string& str) {
    static const std::unordered_map<std::string, TokenType> keywords { 
        { "\n",  token_eol },
        { "(",   token_operator_open_paren },
        { ")",   token_operator_close_paren },
        { "|",   token_operator_absolute, },
        { "=",   token_operator_assign },
        { "+",   token_operator_plus },
        { "-",   token_operator_minus },
        { "*",   token_operator_multiply },
        { "/",   token_operator_divide },
        { "^",   token_operator_exponent },
        { "!",   token_operator_factorial },
        { "mod", token_operator_modulus }
    };

    auto it = keywords.find(str);
    return (it == keywords.end()) ? token_none : it->second;
}

using string_const_iterator = std::string::const_iterator;
using optional_token = std::optional<Token>;

bool isbadwhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}

std::optional<std::string> match_regex_continuously_if_not_empty(const boost::regex& regex, string_const_iterator begin, string_const_iterator end) {
    boost::smatch match;
    boost::regex_search(begin, end, match, regex, boost::match_continuous);
    if (!match[0].str().empty()) {
        return match[0].str();
    } else {
        return {};
    }
}

string_const_iterator get_string_iterator_from_distance_with_cap(const std::string& s, int distance) {
    auto it = s.begin();
    std::advance(it, distance);
    return it;
}

class Lexer
{
public:
    Lexer(std::string source) : m_source{source} {}
    std::vector<Token> Tokenize();
private:
    std::string m_source;
    optional_token m_handle_comment(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_newline(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_operator(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_normalfunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_logarithmicfunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_variable(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_handle_number(std::size_t begin, std::size_t end = std::string::npos);
};

optional_token Lexer::m_handle_comment(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"((\/\/[^\n\r]*\n))", token_none };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_handle_newline(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(\n)", token_eol };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_handle_operator(std::size_t begin, std::size_t end) {
    static const std::vector<TokenInfo> list{
        { R"(\()", token_operator_open_paren },
        { R"(\))", token_operator_close_paren },
        { R"(\|)", token_operator_absolute },
        { R"(=)", token_operator_assign },
        { R"(\+)", token_operator_plus },
        { R"(\-)", token_operator_minus },
        { R"(\*)", token_operator_multiply },
        { R"(\/)", token_operator_divide },
        { R"(\^)", token_operator_exponent },
        { R"(\!)", token_operator_factorial },
        { R"(mod)", token_operator_modulus }
    };

    for (const TokenInfo& obj: list) {
        auto opt_string = match_regex_continuously_if_not_empty(obj.regex(), m_source.begin() + begin, m_source.end());
        if (opt_string) {
            return std::make_optional<Token>(*opt_string, obj.type());
        }
    }

    return {};
}

optional_token Lexer::m_handle_normalfunction(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(sin|cos|tan|ln|floor|ceil|)", token_function_normal };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end()); 
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_handle_logarithmicfunction(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"((log\d*\.?\d*))", token_function_logarithmic };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end()); 
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_handle_variable(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(([[:alpha:]](_\d)?)|)", token_variable };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_handle_number(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(\d*\.?\d+|\d+\.?\d*)", token_literal_number };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> tokens;
    for (std::size_t i = 0; i < m_source.length();) {
        // Skip whitespace
        while (isbadwhitespace(m_source.at(i))) {
            i++;
            if (i >= m_source.length()) {
                return tokens;
            }
        }

        optional_token opt_token;
        if      (opt_token = m_handle_comment(i)) {}
        else if (opt_token = m_handle_newline(i)) {}
        else if (opt_token = m_handle_operator(i)) {}
        else if (opt_token = m_handle_normalfunction(i)) {}
        else if (opt_token = m_handle_logarithmicfunction(i)) {}
        else if (opt_token = m_handle_variable(i)) {}
        else if (opt_token = m_handle_number(i)) {}
        else {
            std::cerr << std::format("Error: Invalid token \"{}\"\n", opt_token->val);
        }

        i += opt_token->len();
        
        if (opt_token->valid()) {
            tokens.push_back(*opt_token);
        }
    }

    return tokens;
}

}; // {anonymous} namespace

namespace brose {

bool Token::valid() {
    return type & token_any && !val.empty();
}

std::size_t Token::len() {
    return val.length();
}

std::string token_type_to_string(TokenType token_type) {
    switch (token_type) {
    default:                return "none";
    case token_any:    return "any";
    case token_eol:         return "end_of_line";
    case token_variable:    return "variable";
    case token_literal_number:      return "number";
    case token_operator_open_paren:  return "open_paren";
    case token_operator_close_paren: return "close_paren";
    case token_operator_assign:      return "assign";
    case token_operator_plus:        return "plus";
    case token_operator_minus:       return "minus";
    case token_operator_multiply:    return "multiply";
    case token_operator_divide:      return "divide";
    case token_operator_exponent:    return "exponent";
    case token_operator_modulus:     return "modulus";
    case token_operator_absolute:    return "absolute";
    case token_operator_factorial:   return "factorial";
    case token_function_normal: return "normal_function";
    case token_function_logarithmic: return "logarithmic_function";
    case token_function_trigonometric: return "trigonometric_function";
    }
}

std::vector<Token> tokenize_source(const std::string& source) {
    Lexer lexer{source};
    return lexer.Tokenize();
}

}; // namespace brose
