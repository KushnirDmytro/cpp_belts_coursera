//
// Created by dkushn on 28.08.19.
//

#include "node.h"
#include "date.h"
#include "token.h"

using namespace std;


const map<string, CompareOps> CompareNode::available_compare_operations = {
        {"<", CompareOps::opLess },
        {"<=", CompareOps::opLessEequal },
        {">", CompareOps::opGreater },
        {">=", CompareOps::opGreaterEqual },
        {"==", CompareOps::opEqualTo },
        {"!=", CompareOps::opNotEqualTo }
};


LogicalOperationNode::LogicalOperationNode(const Token &tok) : nodes_tok_{tok}
{
};

void LogicalOperationNode::SetLeftOperand(const shared_ptr<Node> &new_lhs){
    left_operand_ = new_lhs;
}

void LogicalOperationNode::SetRightOperand(const shared_ptr<Node> &new_rhs){
    right_operand_ = new_rhs;
}

string LogicalOperationNode::GetTokenValue() const {
    return nodes_tok_.value;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event){
    if (left_operand_ != nullptr && right_operand_ != nullptr){
        if (nodes_tok_.value == "AND"){
            return left_operand_->Evaluate(date, event) && right_operand_->Evaluate(date, event);
        } else if (nodes_tok_.value == "OR"){
            return left_operand_->Evaluate(date, event) || right_operand_->Evaluate(date, event);
        } else
            throw logic_error("Tried to evaluate undef logical operator node with value " + nodes_tok_.value);
    }
    else
        throw logic_error("Tried to evaluate undef logical operator node with value " + nodes_tok_.value);
}
