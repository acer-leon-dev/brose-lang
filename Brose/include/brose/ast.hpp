#pragma once
#include <string>
#include <memory>
#include <vector>


namespace brose 
{

enum class TokenType;

/**
 * 
 */
class ExprNode
{
public:
    virtual ~ExprNode() = default;
};

/**
 * 
 */
class VariableExprNode : public ExprNode
{
public:
    VariableExprNode(const std::string& name);

    std::string name;
};

/**
 * 
 */
class NumberExprNode : public ExprNode
{
public:
    NumberExprNode(double value);
    double value;
};

/**
 * 
 */
class AssignmentExprNode : public ExprNode
{
public:
    AssignmentExprNode(std::unique_ptr<VariableExprNode> lhs, std::unique_ptr<ExprNode> rhs);

    std::unique_ptr<VariableExprNode> lhs;
    std::unique_ptr<ExprNode> rhs;
};

/**
 * 
 */
class FunctionCallExprNode : public ExprNode
{
public:
    FunctionCallExprNode(const std::string& name, std::vector<std::unique_ptr<ExprNode>> args);
    
    std::string name;
    std::vector<std::unique_ptr<ExprNode>> args;
};

/**
 * Node for unary operations
 * e.g, |-5|, n!
 */
class UnaryOpExprNode : public ExprNode
{
public:
    UnaryOpExprNode(TokenType op, std::unique_ptr<ExprNode> operand);
        
    TokenType op;
    std::unique_ptr<ExprNode> operand;
};

/**
 * Node for binary operations
 * e.g., (1 + 2), (x mod 3)
 */
class BinaryExprNode : public ExprNode
{
public:
    BinaryExprNode(TokenType op,
        std::unique_ptr<ExprNode> lhs,
        std::unique_ptr<ExprNode> rhs);
        
    TokenType op;
    std::unique_ptr<ExprNode> lhs;
    std::unique_ptr<ExprNode> rhs;
};

}; // namespace brose