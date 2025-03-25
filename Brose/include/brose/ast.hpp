#pragma once
#include <string>
#include <memory>
#include <vector>


namespace brose 
{

enum class TokenTypeO;

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
    UnaryOpExprNode(TokenTypeO op, std::unique_ptr<ExprNode> operand);
        
    TokenTypeO op;
    std::unique_ptr<ExprNode> operand;
};

/**
 * Node for binary operations
 * e.g., (1 + 2), (x mod 3)
 */
class BinaryExprNode : public ExprNode
{
public:
    BinaryExprNode(TokenTypeO op,
        std::unique_ptr<ExprNode> lhs,
        std::unique_ptr<ExprNode> rhs);
        
    TokenTypeO op;
    std::unique_ptr<ExprNode> lhs;
    std::unique_ptr<ExprNode> rhs;
};

}; // namespace brose