// PrintStatement.cpp:
#include "PrintStatement.h"

PrintStatement::PrintStatement(char variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	char var = this->m_variableName;
	std::cout << state->getVariable(var);
	state->incrementCounter();
}
