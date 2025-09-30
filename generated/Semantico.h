#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "SemanticError.h"
#include "Token.h"
#include <map>
#include <vector>

typedef long long max_int;

class Semantico {
private:
  std::map<std::string, max_int> symbols;
  std::vector<max_int> stack;
  std::string id_;

  max_int pop_stack();

public:
  void executeAction(int action, const Token *token);
};

#endif
