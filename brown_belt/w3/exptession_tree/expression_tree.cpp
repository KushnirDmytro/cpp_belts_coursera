//
// Created by dkushn on 29.09.19.
//

#ifndef CPP_BELTS_EXPRESSION_TREE_CPP
#define CPP_BELTS_EXPRESSION_TREE_CPP

#include <string>
#include <sstream>

#include "Common.h"

namespace Expressions{

    class Value : public Expression{
    public:
        Value(int val) : val_{val}{}
        int Evaluate() const final { return val_;};
        std::string ToString() const final { return std::to_string(val_);};
    private:
        int val_;
    };
    
    class Operation : public Expression {
    public:
        Operation(ExpressionPtr lhs, ExpressionPtr rhs) : lhs_{move(lhs)}, rhs_{move(rhs)} {}
        int Evaluate() const override = 0;
        std::string ToString() const final{
            std::stringstream build{""};
            build << '(' <<  lhs_->ToString() << ')'
            << GetOperationChar()
            << '(' << rhs_->ToString() << ')';
            return build.str();
        };
    protected:
        virtual char GetOperationChar() const = 0;
        ExpressionPtr lhs_, rhs_;
    };

    class Sum : public Operation {
    public:
        using Operation::Operation;
        int Evaluate() const override { return lhs_->Evaluate() + rhs_->Evaluate();};
    private:
        char GetOperationChar() const override { return '+'; };
    };

    class Product : public Operation{
    public:
        using Operation::Operation;
        int Evaluate() const override { return lhs_->Evaluate() * rhs_->Evaluate();};
    private:
        char GetOperationChar() const override { return '*'; };
    };
}

ExpressionPtr Value(int value){ return std::make_unique<Expressions::Value>(value); }
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{ return  std::make_unique<Expressions::Sum>(move(left), move(right)); }
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{ return  std::make_unique<Expressions::Product>(move(left), move(right)); }
#endif //CPP_BELTS_EXPRESSION_TREE_CPP
