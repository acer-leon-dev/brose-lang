#pragma once

#include <string>
#include <vector>

namespace brose {

enum TokenType : int {
    token_none                      = 0,
    token_eol                       = 1 <<  0,
    token_variable                  = 1 <<  1,
    token_number                    = 1 <<  2,
    token_open_paren                = 1 <<  3,
    token_close_paren               = 1 <<  4,
    token_assign                    = 1 <<  5,
    token_plus                      = 1 <<  6,
    token_minus                     = 1 <<  7,
    token_multiply                  = 1 <<  8,
    token_divide                    = 1 <<  9,
    token_exponent                  = 1 << 10,
    token_modulus                   = 1 << 11,
    token_absolute                  = 1 << 12,
    token_factorial                 = 1 << 13,
    token_normal_function           = 1 << 14,
    token_logarithmic_function      = 1 << 15,
    token_trigonometric_function    = 1 << 16,

    token_flag_none      = 0,
    token_flag_any       = token_eol | token_variable | token_number 
                    | token_open_paren | token_close_paren | token_assign 
                    | token_plus | token_minus | token_multiply 
                    | token_divide | token_exponent | token_modulus 
                    | token_absolute | token_factorial | token_normal_function 
                    | token_logarithmic_function | token_trigonometric_function
};

struct Token {
    std::string value = "";
    TokenType type = token_flag_none;
    
    bool valid();
    bool operator==(const Token& other) const = default; 
};

std::string token_type_to_string(TokenType token_type);
std::vector<Token> lex(const std::string& src); 

}; // namespace brose
