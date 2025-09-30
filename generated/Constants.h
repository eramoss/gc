#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_BINARY_VALUE = 2,
    t_SUM = 3,
    t_SUB = 4,
    t_DIV = 5,
    t_MUL = 6,
    t_EXP = 7,
    t_LOG = 8,
    t_PRINT = 9,
    t_LPAREN = 10,
    t_RPAREN = 11,
    t_ASSING = 12,
    t_ID = 13,
    t_SEMICOLON = 14,
    t_COMMA = 15
};

const int STATES_COUNT = 22;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 28;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[53][39][2];

extern const int PRODUCTIONS[23][2];

extern const char *PARSER_ERROR[53];

#endif
