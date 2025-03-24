// #include "pch.hpp"
// #include <brose/parser.hpp>
// #include <brose/ast.hpp>
// #include <brose/lexer.hpp>
// #include <brose/operations.hpp>

// using namespace brose;

// // Alias to token vector iterator
// using vectok_iter = std::vector<Token>::const_iterator; 

// namespace
// {

// operations::function get_binary_function_from_token(const Token& token) {
//     if (token.type == TT_LogarithmicFunction) {
//         return operations::log;
//     }

//     throw std::invalid_argument("");
// }

// double get_logarithm_base_from_token(const Token& token) {
//     if (token.value.length() == 3) {
//         return 10;
//     }
    
//     return std::stod(token.value.substr(4));
// }

// int get_binop_precedence(const Token& token) {
//     static const std::unordered_map<TokenType, int>
//     binop_precedence_map = {
//         { TT_Exponent,      10 }, // E 
        
//         { TT_Multiply,       20 }, // M
//         { TT_Divide,      20 }, // D
//         { TT_Modulusulus,        20 },

//         { TT_Plus,       30 }, // A
//         { TT_Minus,      30 }, // S
//     };

//     if (!(static_cast<int>(token.type) & static_cast<int>(TT_AnyOperator))) {
//         return -1;
//     }

//     return binop_precedence_map.at(token.type);
// }

// std::unique_ptr<ExprNode> log_error (const std::string& m) {
//     std::cerr << "Error: " << m << "\n";
//     return nullptr;
// }

// std::unique_ptr<ExprNode> parse_binop_rhs(vectok_iter& it, int expr_prec, std::unique_ptr<ExprNode> lhs) {
//     using namespace operations;
//     while (true) {
//         int tok_prec = get_binop_precedence(*it);
//         if (tok_prec < expr_prec) {
//             return lhs;
//         }

//         binary op = get_binary_operation_from_token(*it);

//         it++;

//         std::unique_ptr<ExprNode> rhs = parse_primary(it);
//         if (!rhs) {
//             return nullptr;
//         }

//         int next_prec = get_binop_precedence(*it);
//         if (tok_prec < next_prec) {
//             rhs = parse_binop_rhs(tok_prec + 1, std::move(rhs));
//         }

//         lhs = std::make_unique<BinaryExprNode>(op, std::move(lhs), std::move(rhs));
//     }
// }

// std::unique_ptr<ExprNode> parse_expression(vectok_iter& it) {
//     auto lhs = parse_primary(it);
//     if (!lhs) {
//         return nullptr;
//     }

//     return parse_binop_rhs(0, std::move(lhs));
// }

// std::unique_ptr<ExprNode> parse_number_expr(vectok_iter& it)  {
//     double num = std::stod(it->value);
//     auto result = std::make_unique<NumberExprNode>(num);
//     it++; // skip number
//     return std::move(result);
// }

// std::unique_ptr<ExprNode> parse_parenthesized_expr(vectok_iter& it) {
//     it++; // skip open paren
//     auto V = parse_expression(it);
//     if (!V) {
//         return nullptr;
//     }

//     if (it->type != TT_CloseParen) {
//         return log_error("expected ')'");
//     }

//     it++; // skip close paren
//     return V;
// }

// std::unique_ptr<ExprNode> parse_variable_expr(vectok_iter& it) {
//     std::string name = it->value;
//     it++; // skip variable
//     return std::make_unique<VariableExprNode>(name); 
// }

// std::unique_ptr<ExprNode> parse_argument(vectok_iter& it) {
//     std::unique_ptr<ExprNode> arg = parse_expression(it);
//     it++;
//     return (arg) ? std::move(arg) : nullptr;
// }

// std::unique_ptr<ExprNode> parse_function_expr(vectok_iter& it) {   
//     operations::function function;
//     std::vector<std::unique_ptr<ExprNode>> args;

//     if (static_cast<int>(it->type) & static_cast<int>(TT_UnaryFunction)) {
//         function = get_unary_function_from_token(*it);
//     }
//     else if (static_cast<int>(it->type) & static_cast<int>(TT_BinaryFunction)) {
//         function = get_binary_function_from_token(*it);

//         if (it->type == TT_LogarithmicFunction) {
//             args.push_back(std::make_unique<NumberExprNode>(get_logarithm_base_from_token(*it)));
//         }
//     }

//     it++; // skip identifier

//     if (auto arg = parse_expression(it)) {
//         args.push_back(std::move(arg));
//     } 
//     else {
//         return nullptr;            
//     }
    
//     if (it->type != TT_CloseParen) {
//         return log_error("Expected ')'");
//     }
//     it++; // skip closing paren

//     return std::make_unique<FunctionCallExprNode>(function, std::move(args));
// }

// std::unique_ptr<ExprNode> parse_primary(vectok_iter& it) {
//     switch (it->type) {
//         case TT_Variable:
//             return parse_variable_expr(it);
//         case TT_Number:
//             return parse_number_expr(it);
//         case TT_OpenParen:
//             return parse_parenthesized_expr(it);
//     }
    
//     if (static_cast<int>(it->type) & static_cast<int>(TT_AnyFunction)) {
//         return parse_function_expr(it);
//     }

//     return log_error(std::format("unknown token \"{}\", expected an expression", it->value));
// }

// };

// namespace brose
// {

// void parse(const std::vector<Token>& tokens) {
    
// }

// };