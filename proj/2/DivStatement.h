#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class DivStatement : public Statement
{
public:
    DivStatement(char var, int val);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    int m_value;
};

#endif
