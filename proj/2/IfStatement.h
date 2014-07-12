#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include <string>
#include "Statement.h"
#include "ProgramState.h"

class IfStatement : public Statement
{
public:
    IfStatement(char var, std::string op, int compare, int dest);
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    char m_variableName;
    std::string m_op;
    int m_comparison;
    int m_destination;
    bool checkCondition(int first_operand, std::string op, int second_operand);
};

#endif
