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

    token_any       = token_eol | token_variable | token_number 
                    | token_open_paren | token_close_paren | token_assign 
                    | token_plus | token_minus | token_multiply 
                    | token_divide | token_exponent | token_modulus 
                    | token_absolute | token_factorial | token_normal_function 
                    | token_logarithmic_function | token_trigonometric_function
};

struct Token {
    /** @brief The string value of this token
     * 
     */
    std::string val = "";

    /** @brief the specific type of this token
     * 
     */
    TokenType type = token_none;
    
    /** @brief Returns true if `*this` is a valid token.
     * A token is a valid token if `this->type & token_flag_any` is true and if `!this->value.empty()`.
     */
    bool valid();

    /** @brief Returns the length of `this->value.length()`.
     * 
     */
    std::size_t len();

    /** @brief Enables equality comparisons between tokens.
     * 
     */
    bool operator==(const Token& other) const = default; 
};

/** @brief Returns a string representation of the given token
 * Returns `"none"` if `!(type & token_any)`
 */
std::string token_type_to_string(TokenType type);

/** @brief Tokenizes the given source code 
 * Converts `src`, the content of a .brose script to a list of tokens.
 */
std::vector<Token> tokenize_source(const std::string& src); 

}; // namespace brose
