#ifndef SYNTATIC_ERROR_H
#define SYNTATIC_ERROR_H

#include "AnalysisError.h"

#include <string>

class SyntacticError : public AnalysisError
{
public:

    SyntacticError(const std::string &msg, int position = -1)
      : AnalysisError(msg, position) { }
};

#endif
