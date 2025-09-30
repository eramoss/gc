#include "Sintatico.h"

void Sintatico::parse(Lexico *scanner, Semantico *semanticAnalyser)
{
    this->scanner = scanner;
    this->semanticAnalyser = semanticAnalyser;

    //Limpa a pilha
    while (! stack.empty())
        stack.pop();

    stack.push(0);

    if (previousToken != 0 && previousToken != currentToken)
        delete previousToken;
    previousToken = 0;

    if (currentToken != 0)
        delete currentToken;
    currentToken = scanner->nextToken();

    while ( ! step() )
        ;
}

bool Sintatico::step()
{
    if (currentToken == 0) //Fim de Sentença
    {
        int pos = 0;
        if (previousToken != 0)
            pos = previousToken->getPosition() + previousToken->getLexeme().size();

        currentToken = new Token(DOLLAR, "$", pos);
    }

    int token = currentToken->getId();
    int state = stack.top();

    const int* cmd = PARSER_TABLE[state][token-1];

    switch (cmd[0])
    {
        case SHIFT:
        {
            stack.push(cmd[1]);
            if (previousToken != 0)
                delete previousToken;
            previousToken = currentToken;
            currentToken = scanner->nextToken();
            return false;
        }
        case REDUCE:
        {
            const int* prod = PRODUCTIONS[cmd[1]];

            for (int i=0; i<prod[1]; i++)
                stack.pop();

            int oldState = stack.top();
            stack.push(PARSER_TABLE[oldState][prod[0]-1][1]);
            return false;
        }
        case ACTION:
        {
            int action = FIRST_SEMANTIC_ACTION + cmd[1] - 1;
            stack.push(PARSER_TABLE[state][action][1]);
            semanticAnalyser->executeAction(cmd[1], previousToken);
            return false;
        }
        case ACCEPT:
            return true;

        case ERROR:
            throw SyntacticError(PARSER_ERROR[state], currentToken->getPosition());
    }
    return false;
}

