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

FunctionCallExprNode::FunctionCallExprNode(FunctionType function, std::vector<std::unique_ptr<ExprNode>> args)
:   function { function },
    args ( std::move(args) )
{
    
}

UnaryOpExprNode::UnaryOpExprNode(UnaryOpType operation, std::unique_ptr<ExprNode> operand)
:   operation { operation },
    operand { std::move(operand) }
{

}


BinaryOpExprNode::BinaryOpExprNode(BinaryOpType operation, std::unique_ptr<ExprNode> leftoperand, std::unique_ptr<ExprNode> rightoperand)
:   operation { operation },
    leftoperand { std::move(leftoperand) },
    rightoperand { std::move(rightoperand) }
{
    
}


}; // namespace brose