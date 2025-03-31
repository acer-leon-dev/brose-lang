#pragma once

#include <string>
#include <vector>

namespace brose {

enum TokenType : int {
    token_none                      = 0,
    token_eol                       = 1 <<  0,
    token_variable                  = 1 <<  1,
    token_literal_number            = 1 <<  2,
    token_operator_open_paren       = 1 <<  3,
    token_operator_close_paren      = 1 <<  4,
    token_operator_assign           = 1 <<  5,
    token_operator_plus             = 1 <<  6,
    token_operator_minus            = 1 <<  7,
    token_operator_multiply         = 1 <<  8,
    token_operator_divide           = 1 <<  9,
    token_operator_exponent         = 1 << 10,
    token_operator_modulus          = 1 << 11,
    token_operator_absolute         = 1 << 12,
    token_operator_factorial        = 1 << 13,
    token_function_normal           = 1 << 14,
    token_function_logarithmic      = 1 << 15,
    token_function_trigonometric    = 1 << 16,

    token_any   = token_eol
                | token_variable
                | token_literal_number
                | token_operator_open_paren
                | token_operator_close_paren
                | token_operator_assign
                | token_operator_plus
                | token_operator_minus
                | token_operator_multiply
                | token_operator_divide
                | token_operator_exponent
                | token_operator_modulus
                | token_operator_absolute
                | token_operator_factorial
                | token_function_normal
                | token_function_logarithmic
                | token_function_trigonometric
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
