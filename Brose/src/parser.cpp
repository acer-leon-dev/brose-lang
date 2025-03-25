#include "pch.hpp"
#include <brose/parser.hpp>
#include <brose/ast.hpp>
#include <brose/lexer.hpp>
#include <brose/operations.hpp>

using namespace brose;

// Alias to token vector iterator
using TokenVecIt = std::vector<Token>::const_iterator; 

namespace
{

operations::function get_binary_function_from_token(const Token& token) {
    if (token.type == token_logarithmic_function) {
        return operations::log;
    }

    throw std::invalid_argument("");
}

double get_logarithm_base_from_token(const Token& token) {
    if (token.value.length() == 3) {
        return 10;
    }
    
    return std::stod(token.value.substr(4));
}

int get_binop_precedence(const Token& token) {
    static const std::unordered_map<TokenType, int>
    binop_precedence_map = {
        { token_exponent,   10 }, // E 
        
        { token_multiply,   20 }, // M
        { token_divide,     20 }, // D
        { token_modulus,    20 },

        { token_plus,       30 }, // A
        { token_minus,      30 }, // S
    };

    int AnyOperator   = token_open_paren | token_close_paren | token_assign | token_plus 
                            | token_minus | token_multiply | token_divide | token_exponent 
                            | token_modulus | token_absolute | token_factorial;

    if (!(token.type & AnyOperator)) {
        return -1;
    }

    return binop_precedence_map.at(token.type);
}

std::unique_ptr<ExprNode> log_error (const std::string& m) {
    std::cerr << "Error: " << m << "\n";
    return nullptr;
}

std::unique_ptr<ExprNode> parse_binop_rhs(TokenVecIt& it, int expr_precedence, std::unique_ptr<ExprNode> lhs) {
    using namespace operations;
    while (true) {
        int tok_prec = get_binop_precedence(*it);
        if (tok_prec < expr_precedence) {
            return lhs;
        }

        TokenType op = it->type;
        it++;

        std::unique_ptr<ExprNode> rhs = parse_primary(it);
        if (!rhs) {
            return nullptr;
        }

        int next_prec = get_binop_precedence(*it);
        if (tok_prec < next_prec) {
            rhs = parse_binop_rhs(it, tok_prec + 1, std::move(rhs));
        }

        lhs = std::make_unique<BinaryExprNode>(op, std::move(lhs), std::move(rhs));
    }
}

std::unique_ptr<ExprNode> parse_expression(TokenVecIt& it) {
    auto lhs = parse_primary(it);
    if (!lhs) {
        return nullptr;
    }

    return parse_binop_rhs(it, 0, std::move(lhs));
}

std::unique_ptr<ExprNode> parse_number_expr(TokenVecIt& it)  {
    double num = std::stod(it->value);
    auto result = std::make_unique<NumberExprNode>(num);
    it++; // skip number
    return std::move(result);
}

std::unique_ptr<ExprNode> parse_parenthesized_expr(TokenVecIt& it) {
    it++; // skip open paren
    auto V = parse_expression(it);
    if (!V) {
        return nullptr;
    }

    if (it->type != token_close_paren) {
        return log_error("expected ')'");
    }

    it++; // skip close paren
    return V;
}

std::unique_ptr<ExprNode> parse_variable_expr(TokenVecIt& it) {
    std::string name = it->value;
    it++; // skip variable
    return std::make_unique<VariableExprNode>(name); 
}

std::unique_ptr<ExprNode> parse_argument(TokenVecIt& it) {
    std::unique_ptr<ExprNode> arg = parse_expression(it);
    it++;
    return (arg) ? std::move(arg) : nullptr;
}

std::unique_ptr<ExprNode> parse_function_expr(TokenVecIt& it) {   
    operations::function function;
    std::vector<std::unique_ptr<ExprNode>> args;

    if (it->type & token_normal_function | token_trigonometric_function) {
        function = get_unary_function_from_token(*it);
    } else if (it->type & token_logarithmic_function) {
        function = get_binary_function_from_token(*it);

        if (it->type == token_logarithmic_function) {
            args.push_back(std::make_unique<NumberExprNode>(get_logarithm_base_from_token(*it)));
        }
    }

    it++; // skip identifier

    if (auto arg = parse_expression(it)) {
        args.push_back(std::move(arg));
    } else {
        return nullptr;            
    }
    
    if (it->type != token_close_paren) {
        return log_error("Expected \')\'");
    }
    it++; // skip closing paren

    return std::make_unique<FunctionCallExprNode>(function, std::move(args));
}

std::unique_ptr<ExprNode> parse_primary(TokenVecIt& it) {
    switch (it->type) {
    case token_variable:
        return parse_variable_expr(it);
    case token_number:
        return parse_number_expr(it);
    case token_open_paren:
        return parse_parenthesized_expr(it);
    }
    
    if (static_cast<int>(it->type) & static_cast<int>(token_any)) {
        return parse_function_expr(it);
    }

    return log_error(std::format("unknown token \"{}\", expected an expression", it->value));
}

};

namespace brose
{

void parse(const std::vector<Token>& tokens) {
    
}

};