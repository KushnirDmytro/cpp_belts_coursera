#pragma once

#include <sstream>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;

enum class TokenType {
  DATE,
  EVENT,
  COLUMN,
  LOGICAL_OP,
  COMPARE_OP,
  PAREN_LEFT,
  PAREN_RIGHT,
};

struct Token {
  const string value;
  const TokenType type;
};

ostream& operator<<(ostream& os, const Token &t);
ostream& operator<<(ostream& os, const vector<Token> &t);


vector<Token> Tokenize(istream& cl);
