//
// Created by dkushn on 28.08.19.
//

#include "node.h"
#include "date.h"
#include "token.h"

using namespace std;


//const map<string, CompareOps> CompareNode::available_compare_operations = {
//        {"<", CompareOps::opLess },
//        {"<=", CompareOps::opLessEequal },
//        {">", CompareOps::opGreater },
//        {">=", CompareOps::opGreaterEqual },
//        {"==", CompareOps::opEqualTo },
//        {"!=", CompareOps::opNotEqualTo }
//};


//LogicalOperationNode::LogicalOperationNode(const Token &tok) : nodes_tok_{tok}
//{
//};

void LogicalOperationNode::SetLeftOperand(const shared_ptr<Node> &new_lhs){
    left_operand_ = new_lhs;
}

void LogicalOperationNode::SetRightOperand(const shared_ptr<Node> &new_rhs){
    right_operand_ = new_rhs;
}

LogicalOperation LogicalOperationNode::GetOperation() const {
    return op_;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event){
    if (left_operand_ != nullptr && right_operand_ != nullptr){
        if (op_ == LogicalOperation::And){
            return left_operand_->Evaluate(date, event) && right_operand_->Evaluate(date, event);
        } else if (op_ == LogicalOperation::Or){
            return left_operand_->Evaluate(date, event) || right_operand_->Evaluate(date, event);
        } else
            throw logic_error("Tried to evaluate undef logical operator node with value ");
    }
    else
        throw logic_error("Tried to evaluate undef logical operator node with value " );
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &op, const shared_ptr<Node> &lhs,
                                           const shared_ptr<Node> &rhs
                                           ) : op_{op}, left_operand_{lhs}, right_operand_{rhs}
                                           {

                                           }

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    switch (cmp_){
        case Comparison ::Less :
            return date < comp_with_;
        case Comparison::LessOrEqual :
            return date <= comp_with_;
        case Comparison::Greater :
            return date > comp_with_;
        case Comparison::GreaterOrEqual :
            return date >= comp_with_;
        case Comparison::Equal :
            return date == comp_with_;
        case Comparison::NotEqual :
            return date != comp_with_;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) {
    switch (cmp_){
        case Comparison ::Less :
            return event < comp_with_;
        case Comparison::LessOrEqual :
            return event <= comp_with_;
        case Comparison::Greater :
            return event > comp_with_;
        case Comparison::GreaterOrEqual :
            return event >= comp_with_;
        case Comparison::Equal :
            return event == comp_with_;
        case Comparison::NotEqual :
            return event != comp_with_;
    }
}
