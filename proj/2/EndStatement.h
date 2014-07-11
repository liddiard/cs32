#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class EndStatement : public Statement
{
public:
    EndStatement();
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    int m_value;
};

#endif
