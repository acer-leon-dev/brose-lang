#pragma once
#include <string>
#include <memory>
#include <brose/operations.hpp>

namespace brose 
{

class ExprNode
{
public:
    virtual ~ExprNode() = default;
};

class VariableExprNode : public ExprNode
{
public:
    VariableExprNode(
        const std::string& name)
    :   name { name }
    {

    }

    std::string name;
};

class NumberExprNode : public ExprNode
{
public:
    NumberExprNode(
        double value)
    :   value { value }
    {

    }
    
    double value;
};

class AssignmentExprNode : public ExprNode
{
public:
    AssignmentExprNode(
        std::unique_ptr<VariableExprNode> lhs,
        std::unique_ptr<ExprNode> rhs)
    :   lhs { std::move(lhs) },
        rhs { std::move(rhs) }
    {

    }

    std::unique_ptr<VariableExprNode> lhs;
    std::unique_ptr<ExprNode> rhs;
};

class UnaryFunctionExprNode : public ExprNode
{
public:
    UnaryFunctionExprNode(
        const std::string& name,
        unary_function func)
    :   name { name },
        func { func }
    {

    }
    
    std::string name;
    unary_function func;
};

class CallExprNode : public ExprNode
{
public:
    CallExprNode(
        std::unique_ptr<UnaryFunctionExprNode> function)
    :   function { std::move(function) }
    {

    }

    std::unique_ptr<UnaryFunctionExprNode> function;
};

/**
 * Node for binary operations
 * e.g., (1 + 2), (x mod 3)
 */
class BinaryExprNode : public ExprNode
{
public:
    BinaryExprNode(
        std::unique_ptr<ExprNode> lhs,
        std::unique_ptr<ExprNode> rhs)
    :   lhs { std::move(lhs) },
        rhs { std::move(rhs) }
    {

    }

    std::unique_ptr<ExprNode> lhs;
    std::unique_ptr<ExprNode> rhs;
};

/**
 * Node for unary operations
 * e.g, |-5|, n!
 */
class UnaryExprNode : public ExprNode
{
public:
    std::unique_ptr<ExprNode> expr;
};

class AddExprNode : public BinaryExprNode
{
public:

};

class SubExprNode : public BinaryExprNode
{
public:

};

class MulExprNode : public BinaryExprNode
{
public:

};

class DivExprNode : public BinaryExprNode
{
public:

};

class ExpExprNode : public BinaryExprNode
{
public:

};

class ModExprNode : public BinaryExprNode
{
public:

};

class AbsExprNode : public UnaryExprNode
{
public:

};

class FacExprNode : public UnaryExprNode
{
public:

};

}; // namespace brose