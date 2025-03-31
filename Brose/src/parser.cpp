#include "pch.hpp"
#include <brose/parser.hpp>
#include <brose/ast.hpp>
#include <brose/lexer.hpp>
#include <brose/operations.hpp>

namespace {

using namespace brose;
using token_it_ref = std::vector<Token>::const_iterator&; 
using expr_node_uptr = std::unique_ptr<ExprNode>;

int            get_binop_precedence (const Token& token);
expr_node_uptr log_error            (const std::string& message);
expr_node_uptr parse_argument       (token_it_ref it);
expr_node_uptr parse_binop_rhs      (token_it_ref it, int expr_precedence, expr_node_uptr expr_left);
expr_node_uptr parse_expression     (token_it_ref it);
expr_node_uptr parse_function_expr  (token_it_ref it);
expr_node_uptr parse_number_expr    (token_it_ref it);
expr_node_uptr parse_paren_expr     (token_it_ref it);
expr_node_uptr parse_primary        (token_it_ref it);
expr_node_uptr parse_variable_expr  (token_it_ref it);

int get_binop_precedence(const Token& token) {
    static const std::unordered_map<TokenType, int>
    binary_operator_precedence_map = {
        { token_operator_exponent, 10 }, // E 
        { token_operator_multiply, 20 }, // M
        { token_operator_divide,   20 }, // D
        { token_operator_modulus,  20 },
        { token_operator_plus,     30 }, // A
        { token_operator_minus,    30 }, // S
    };

    static int token_flag_any_operator   = token_operator_open_paren | token_operator_close_paren | token_operator_assign | token_operator_plus 
                            | token_operator_minus | token_operator_multiply | token_operator_divide | token_operator_exponent 
                            | token_operator_modulus | token_operator_absolute | token_operator_factorial;
                            
    if (token.type & token_flag_any_operator) {
        return binary_operator_precedence_map.at(token.type);
    }

    return -1;
}

expr_node_uptr log_error(const std::string& m) {
    std::cerr << "Error: " << m << "\n";
    return nullptr;
}

expr_node_uptr parse_binop_rhs(token_it_ref it, int precedence, expr_node_uptr expr_left) {
    while (true) {
        // Determine precedence of [this-op]
        int this_token_precedence = get_binop_precedence(*it);
        if (this_token_precedence < precedence) {
            return expr_left; // Return left hand, e.g., [a] + b
        }

        // Evaluate operator type
        TokenType bin_op = it->type;
        it++; // Skip operator

        // Parse right hand expression, e.g., a + [b]
        auto expr_right = parse_primary(it);
        if (!expr_right) {
            return nullptr;
        }

        // Evaluate the prec. of the next operation
        int next_token_precedence = get_binop_precedence(*it);
        // Check if [this-op] has lower prec. than [next-op]
        // If so...
        if (this_token_precedence < next_token_precedence) {
            // ...evaluate [next-expr] first & use result as operand for [this-expr]
            expr_right = parse_binop_rhs(it, this_token_precedence + 1, std::move(expr_right));
            if (!expr_right) {
                return nullptr;
            }
        }

        // Finally return this expression when [this-prec] is higher or equal to following precs.
        expr_left = std::make_unique<BinaryExprNode>(bin_op, std::move(expr_left), std::move(expr_right));
    }
}

expr_node_uptr parse_expression(token_it_ref it) {
    auto expr_left = parse_primary(it);
    return (expr_left) ? parse_binop_rhs(it, 0, std::move(expr_left)) : nullptr;
}

expr_node_uptr parse_number_expr(token_it_ref it)  {
    double num = std::stod(it->val);
    auto result = std::make_unique<NumberExprNode>(num);
    it++; // skip number
    return std::move(result);
}

expr_node_uptr parse_paren_expr(token_it_ref it) {
    it++; // skip open paren
    
    auto V = parse_expression(it);
    if (!V) {
        return nullptr;
    }

    if (it->type != token_operator_close_paren) {
        return log_error("expected ')'");
    }

    it++; // skip close paren
    return V;
}

expr_node_uptr parse_variable_expr(token_it_ref it) {
    std::string name = it->val;
    it++; // skip variable
    return std::make_unique<VariableExprNode>(std::move(name)); 
}

expr_node_uptr parse_function_expr(token_it_ref it) { 
    // static int token_flag_unary_function = token_normal_function | token_trigonometric_function;
    // static int token_flag_binary_function = token_logarithmic_function;
    auto node = std::make_unique<FunctionCallExprNode>("", std::vector<expr_node_uptr>());

    if (it->type & token_function_logarithmic) {
        // Set identifier to generic name
        node->name = "log";
        
        // Get base argument
        double base = (it->val.length() == 3) ? 10 : std::stod(it->val.substr(4));
        node->args.push_back(std::make_unique<NumberExprNode>(base));
    }
    
    it++; // Identifier
    it++; // Open parenthesis
    
    // Get next argument
    if (auto arg = parse_expression(it)) {
        node->args.push_back(std::move(arg));
    } else {
        return nullptr;       
    }
    
    // Check for closing parenthesis
    if (it->type != token_operator_close_paren) {
        return log_error("Expected \')\'");
    }
    
    it++; // Skip closing paren

    return std::move(node);
}

expr_node_uptr parse_primary(token_it_ref it) {
    switch (it->type) {
    case token_variable:    return parse_variable_expr(it);
    case token_literal_number:  return parse_number_expr(it);
    case token_operator_open_paren:  return parse_paren_expr(it);
    }

    int token_function = token_function_normal | token_function_logarithmic | token_function_trigonometric;
    if (it->type & token_function) {
        return parse_function_expr(it);
    }

    return log_error(std::format("unknown token \"{}\", expected an expression", it->val));
}

};

namespace brose
{

void parse(const std::vector<Token>& tokens) {
    
}

};