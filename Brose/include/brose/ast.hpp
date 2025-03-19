#pragma once
#include <string>
#include <memory>
#include <brose/operations.hpp>

namespace brose 
{

enum class FunctionType
{
    log,
    ln,
    sin,
    cos,
    tan,
    floor,
    ceil
};

enum class UnaryOpType
{
    abs,
    fac
};

enum class BinaryOpType
{
    add,
    sub,
    mul,
    div,
    exp,
    mod
};

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
    FunctionCallExprNode(FunctionType function, std::vector<std::unique_ptr<ExprNode>> args);
    
    FunctionType function;
    std::vector<std::unique_ptr<ExprNode>> args;
};

/**
 * Node for unary operations
 * e.g, |-5|, n!
 */
class UnaryOpExprNode : public ExprNode
{
public:
    UnaryOpExprNode::UnaryOpExprNode(UnaryOpType operation, 
        std::unique_ptr<ExprNode> operand);
        
    UnaryOpType operation;
    std::unique_ptr<ExprNode> operand;
};

/**
 * Node for binary operations
 * e.g., (1 + 2), (x mod 3)
 */
class BinaryOpExprNode : public ExprNode
{
public:
    BinaryOpExprNode(BinaryOpType operation,
        std::unique_ptr<ExprNode> leftoperand,
        std::unique_ptr<ExprNode> rightoperand);

    BinaryOpType operation;
    std::unique_ptr<ExprNode> leftoperand;
    std::unique_ptr<ExprNode> rightoperand;
};

}; // namespace brose