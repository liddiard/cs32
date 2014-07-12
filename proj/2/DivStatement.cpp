#include <stdlib.h>
#include <iostream>
#include "DivStatement.h"
using namespace std;

DivStatement::DivStatement(char var, int value)
    : m_variableName( var ), m_value ( value )
{}

void DivStatement::execute(ProgramState * state, ostream &outf)
{
    char var = this->m_variableName;
    int val = this->m_value;
    if (val == 0)
    {
    	cout << "Divide by zero exception";
    	exit(1);
    }
    int original_val = state->getVariable(var);
    int new_val = original_val / val;
    state->setVariable(var, new_val);
    state->incrementCounter();
}
