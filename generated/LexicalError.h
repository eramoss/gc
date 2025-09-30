#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H

#include "AnalysisError.h"

#include <string>

class LexicalError : public AnalysisError
{
public:

    LexicalError(const std::string &msg, int position = -1)
      : AnalysisError(msg, position) { }
};

#endif
