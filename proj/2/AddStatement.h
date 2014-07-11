#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class AddStatement : public Statement
{
public:
    AddStatement(char var, int val);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    int m_value;
};

#endif
