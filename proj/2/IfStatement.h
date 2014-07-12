#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement : public Statement
{
public:
    IfStatement(char var, char op, int compare, int dest);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    char m_op;
    int m_comparison;
    int m_destination;
    bool checkCondition(int first_operand, char op, int second_operand);
};

#endif
