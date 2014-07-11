#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class MultStatement : public Statement
{
public:
    MultStatement(char var, int val);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    int m_value;
};

#endif
