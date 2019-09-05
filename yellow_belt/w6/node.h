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


class Node {
public:

    Node()= default;

    virtual bool Evaluate(const Date& date, const string& event) = 0;
};



class EmptyNode : public Node{
public:
    bool Evaluate(const Date& date, const string& event) override{
        return true;
    }
};

class LogicalOperationNode : public Node {
    shared_ptr<Node> left_operand_;
    shared_ptr<Node> right_operand_;
//    const Token nodes_tok_;
    const LogicalOperation op_;
public:
//    explicit LogicalOperationNode(const Token &tok);
    LogicalOperationNode(const LogicalOperation &op, const shared_ptr<Node> &lhs, const shared_ptr<Node> &rhs);
    void SetLeftOperand(const shared_ptr<Node> &new_lhs);
    void SetRightOperand(const shared_ptr<Node> &new_rhs);
//    string GetTokenValue() const;
    bool Evaluate(const Date& date, const string& event) override;

    LogicalOperation GetOperation() const;
};

class DateComparisonNode : public Node{
    const Comparison cmp_;
    const Date comp_with_;
public:
    DateComparisonNode(const Comparison &cmp, const Date &compare_with) : cmp_{cmp}, comp_with_{compare_with}
    {};
    bool Evaluate(const Date& date, const string& event) override;
};

class EventComparisonNode : public Node{
    const Comparison cmp_;
    const string comp_with_;
public:
    EventComparisonNode(const Comparison &cmp, const string &compare_with) : cmp_{cmp}, comp_with_{compare_with}
    {};
    bool Evaluate(const Date& date, const string& event) override;
};


//EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode