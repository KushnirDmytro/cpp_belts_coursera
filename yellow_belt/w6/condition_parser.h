#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> comparison_node_builder (const vector<Token> &toks);
shared_ptr<Node> condition_builder(const vector<Token> &toks);
vector<Token>::const_iterator next_logical_op_position(const vector<Token>::const_iterator &old_iter_position, const vector<Token> &toks);
shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
