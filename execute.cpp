#include "Token.h"
#include <iostream>

void execute(int action, const Token *token) {
  std::cout << "From execute Ação: " << action << ", Token: " << token->getId()
            << ", Lexema: " << token->getLexeme() << std::endl;
}
