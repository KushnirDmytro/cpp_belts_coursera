//
// Created by dkushn on 28.08.19.
//
#pragma once


#include <string>
#include <memory>
#include <functional>
#include <map>

#include "node.h"
#include "date.h"
#include "token.h"

using namespace std;


class Node {
//    shared_ptr<Node> lhs{nullptr};
//    shared_ptr<Node> rhs{nullptr};
public:

    Node()
    {
    };

    virtual bool Evaluate(const Date& date, const string& event) {
        return true;
        // FIXME!
    }
};

enum class LogicalOperation{
    Or,
    And
};

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class CompareOps{
    opLess,
    opLessEequal,
    opGreater,
    opGreaterEqual,
    opEqualTo,
    opNotEqualTo
};

//template <typename ValType>
class CompareNode : public Node{
private:

    const Token compare_by_;
    const Token compare_op_; // todo template function defined at the moment of object creation
    const Token compare_with_;

    static const map<string, CompareOps> available_compare_operations;


public:

    CompareNode(const Token &compare_by, const Token &compare_op, const Token &compare_with)
            : compare_by_{compare_by}, compare_op_{compare_op}, compare_with_{compare_with}
    {

    }

    template <typename Val>
    bool Comparator(const Val &lhs, const Val &rhs) const {

        CompareOps compareOp = available_compare_operations.at(compare_op_.value);

        switch (compareOp){
            case CompareOps::opLess :
                return lhs < rhs;
            case CompareOps::opLessEequal :
                return lhs <= rhs;
            case CompareOps::opGreater :
                return lhs > rhs;
            case CompareOps::opGreaterEqual :
                return lhs >= rhs;
            case CompareOps::opEqualTo :
                return lhs == rhs;
            case CompareOps::opNotEqualTo :
                return lhs != rhs;
        }

    }

    bool Evaluate(const Date& date, const string& event) override {
        if (compare_with_.type == TokenType::DATE){
            stringstream ss(compare_with_.value);
            return Comparator<Date>(date, ParseDate(ss));
        } else if (compare_with_.type == TokenType::EVENT){
            return Comparator<string>(event, compare_with_.value);
        } else {
            throw invalid_argument("not supported type of token");
        }
    }

};


class EmptyNode : public Node{

};

class LogicalOperationNode : public Node{
    shared_ptr<Node> left_operand_ {nullptr};
    shared_ptr<Node> right_operand_ {nullptr};
    const Token nodes_tok_;
public:
    explicit LogicalOperationNode(const Token &tok);
    void SetLeftOperand(const shared_ptr<Node> &new_lhs);
    void SetRightOperand(const shared_ptr<Node> &new_rhs);
    string GetTokenValue() const;
    bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public CompareNode{

};

class EventComparisonNode : public CompareNode{

};


//EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode