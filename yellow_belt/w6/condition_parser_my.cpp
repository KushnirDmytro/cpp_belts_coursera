//
// Created by dkushn on 28.08.19.
//

#include <algorithm>
#include <vector>
#include <string>
#include <istream>
#include <iterator>

#include "condition_parser_my.h"
#include "token.h"


shared_ptr<Node> comparison_node_builder (const vector<Token> &toks) {
    if ( (toks.size() == 3) &&
         ( (toks[2].type == TokenType::EVENT || toks[2].type == TokenType::DATE)
           && toks[0].type == TokenType::COLUMN
           && toks[1].type == TokenType::COMPARE_OP)
            ) {
        return make_shared<CompareNode>(toks[0], toks[1], toks[2]);
    }
    else {
        stringstream os;
        os << "Unknown token configuration :[" << toks << ']';
        throw logic_error( os.str() );
    }
}


vector<Token>::const_iterator next_logical_op_position(const vector<Token>::const_iterator &old_iter_position, const vector<Token> &toks) {

    vector<Token>::const_iterator new_logiacal_op_pos = find_if(old_iter_position, toks.end(),
                                                                [](const Token &t) {
                                                                    return t.type == TokenType::LOGICAL_OP;
                                                                });
    auto open_brace_in_range = find_if(old_iter_position, new_logiacal_op_pos,
                                       [](const Token &t) { return t.type == TokenType::PAREN_LEFT; });

    if (open_brace_in_range != new_logiacal_op_pos) {
        auto paired_closing_brace = find_if(toks.rbegin(), make_reverse_iterator(old_iter_position),
                                            [](const Token &t) { return t.type == TokenType::PAREN_RIGHT; })
                .base();
        if (paired_closing_brace == old_iter_position) {
            throw logic_error("failed to find paired closing brace");
        }

        new_logiacal_op_pos = find_if(paired_closing_brace, toks.end(),
                                      [](const Token &t) { return t.type == TokenType::LOGICAL_OP; });
    }
    return new_logiacal_op_pos;
}

shared_ptr<Node> condition_builder(const vector<Token> &toks){

    // strip braces
    if (toks.front().type == TokenType::PAREN_LEFT && toks.back().type == TokenType::PAREN_RIGHT){
        return condition_builder( {next(toks.begin()),  prev(toks.end()) });
    }

    shared_ptr<LogicalOperationNode> active_root = nullptr;
    shared_ptr<LogicalOperationNode> new_root_candidate = nullptr;
    auto token_range_lhs = toks.begin();

    for(auto current_op_node = next_logical_op_position(token_range_lhs, toks);
    current_op_node != toks.end();
    current_op_node = next_logical_op_position(token_range_lhs, toks)
//   , token_range_lhs = next(current_op_node) // TODO ask ilidar
            )
    {
        new_root_candidate = make_shared<LogicalOperationNode>(*current_op_node);
        if (active_root != nullptr){
            if (active_root->GetTokenValue() == "OR" && current_op_node->value == "AND"){
                new_root_candidate->SetLeftOperand( condition_builder( {token_range_lhs, current_op_node} )  );
                active_root->SetRightOperand(new_root_candidate);
            } else {
                active_root->SetRightOperand(condition_builder({token_range_lhs, current_op_node}));
                new_root_candidate->SetLeftOperand(active_root);
                active_root = new_root_candidate;
            }
        } else {
            vector<Token> subtoks {toks.begin(), current_op_node};
            new_root_candidate->SetLeftOperand(condition_builder(subtoks));
            active_root = new_root_candidate;
        }
        token_range_lhs = next(current_op_node);
    }

    // processing tail after last logic node if any
    if ( new_root_candidate != nullptr){
        new_root_candidate->SetRightOperand( condition_builder({token_range_lhs, toks.end()}));
    } else  {
        return comparison_node_builder(toks);
    }

    return active_root;
}

shared_ptr<Node> ParseCondition(istream& is){
    vector<Token> toks = Tokenize(is);
    vector<Node> nodes;
    return  condition_builder(toks);
}
