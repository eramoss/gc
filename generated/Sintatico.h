#ifndef Sintatico_H
#define Sintatico_H

#include "Constants.h"
#include "Token.h"
#include "Lexico.h"
#include "Semantico.h"
#include "SyntacticError.h"

#include <stack>

class Sintatico
{
public:
    Sintatico() : previousToken(0), currentToken(0) { }

    ~Sintatico()
    {
        if (previousToken != 0 && previousToken != currentToken) delete previousToken;
        if (currentToken != 0)  delete currentToken;
    }

    void parse(Lexico *scanner, Semantico *semanticAnalyser);

private:
    std::stack<int> stack;
    Token *previousToken;
    Token *currentToken;
    Lexico *scanner;
    Semantico *semanticAnalyser;

    bool step();
};

#endif
