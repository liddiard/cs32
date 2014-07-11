#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class SubStatement : public Statement
{
public:
    SubStatement(char var, int val);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    int m_value;
};

#endif
