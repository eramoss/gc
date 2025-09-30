#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Token.h"
#include "SemanticError.h"

class Semantico
{
public:
    void executeAction(int action, const Token *token);
};

#endif
