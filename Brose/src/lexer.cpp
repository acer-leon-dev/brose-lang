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
    optional_token m_HandleComment(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleNewline(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleOperator(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleNormalFunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleLogarithmicFunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleVariable(std::size_t begin, std::size_t end = std::string::npos);
    optional_token m_HandleNumber(std::size_t begin, std::size_t end = std::string::npos);
};

optional_token Lexer::m_HandleComment(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"((\/\/[^\n\r]*\n))", token_none };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_HandleNewline(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(\n)", token_eol };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_HandleOperator(std::size_t begin, std::size_t end) {
    static const std::vector<TokenInfo> list{
        { R"(\()", token_open_paren },
        { R"(\))", token_close_paren },
        { R"(\|)", token_absolute },
        { R"(=)", token_assign },
        { R"(\+)", token_plus },
        { R"(\-)", token_minus },
        { R"(\*)", token_multiply },
        { R"(\/)", token_divide },
        { R"(\^)", token_exponent },
        { R"(\!)", token_factorial },
        { R"(mod)", token_modulus }
    };

    for (const TokenInfo& obj: list) {
        auto opt_string = match_regex_continuously_if_not_empty(obj.regex(), m_source.begin() + begin, m_source.end());
        if (opt_string) {
            return std::make_optional<Token>(*opt_string, obj.type());
        }
    }

    return {};
}

optional_token Lexer::m_HandleNormalFunction(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(sin|cos|tan|ln|floor|ceil|)", token_normal_function };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end()); 
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_HandleLogarithmicFunction(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"((log\d*\.?\d*))", token_logarithmic_function };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end()); 
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_HandleVariable(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(([[:alpha:]](_\d)?)|)", token_variable };
    auto opt_value = match_regex_continuously_if_not_empty(token_info_obj.regex(), m_source.begin() + begin, m_source.end());
    if (opt_value) {
        return std::make_optional<Token>(*opt_value, token_info_obj.type());
    }

    return {};
}

optional_token Lexer::m_HandleNumber(std::size_t begin, std::size_t end) {
    static const TokenInfo token_info_obj { R"(\d*\.?\d+|\d+\.?\d*)", token_number };
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
        if      (opt_token = m_HandleComment(i)) {}
        else if (opt_token = m_HandleNewline(i)) {}
        else if (opt_token = m_HandleOperator(i)) {}
        else if (opt_token = m_HandleNormalFunction(i)) {}
        else if (opt_token = m_HandleLogarithmicFunction(i)) {}
        else if (opt_token = m_HandleVariable(i)) {}
        else if (opt_token = m_HandleNumber(i)) {}
        else {
            std::cerr << std::format("Error: Invalid token \"{}\"\n", opt_token->value);
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
    return type & token_flag_any && !value.empty();
}

std::size_t Token::len() {
    return value.length();
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
    case token_normal_function: return "normal_function";
    case token_logarithmic_function: return "logarithmic_function";
    case token_trigonometric_function: return "trigonometric_function";
    }
}

std::vector<Token> tokenize_source(const std::string& source) {
    Lexer lexer{source};
    return lexer.Tokenize();
}

}; // namespace brose
