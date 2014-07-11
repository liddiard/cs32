#include "AddStatement.h"
using namespace std;

AddStatement::AddStatement(char var, int value)
    : m_variableName( var ), m_value ( value )
{}

void AddStatement::execute(ProgramState * state, ostream &outf)
{
    char var = this->m_variableName;
    int val = this->m_value;
    int original_val = state->getVariable(var);
    int new_val = original_val + val;
    state->setVariable(var, new_val);
    state->incrementCounter();
}
