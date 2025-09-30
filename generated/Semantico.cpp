#include "Semantico.h"
#include "Constants.h"

extern void execute(int action, const Token *token);

void Semantico::executeAction(int action, const Token *token) {
  execute(action, token);
}
