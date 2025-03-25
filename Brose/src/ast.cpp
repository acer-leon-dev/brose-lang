#include <brose/ast.hpp>

namespace brose 
{

VariableExprNode::VariableExprNode(const std::string& name)
:   name { name }
{

}

NumberExprNode::NumberExprNode(double value)
:   value { value }
{

}

AssignmentExprNode::AssignmentExprNode(std::unique_ptr<VariableExprNode> lhs, std::unique_ptr<ExprNode> rhs)
:   lhs { std::move(lhs) },
    rhs { std::move(rhs) }
{

}

FunctionCallExprNode::FunctionCallExprNode(const std::string& name, std::vector<std::unique_ptr<ExprNode>> args)
:   name { name },
    args ( std::move(args) )
{
    
}

UnaryOpExprNode::UnaryOpExprNode(TokenTypeO op, std::unique_ptr<ExprNode> operand)
:   op { op },
    operand { std::move(operand) }
{

}


BinaryExprNode::BinaryExprNode(TokenTypeO op, std::unique_ptr<ExprNode> lhs, std::unique_ptr<ExprNode> rhs)
:   op { op },
    lhs { std::move(lhs) },
    rhs { std::move(rhs) }
{
    
}


}; // namespace brose