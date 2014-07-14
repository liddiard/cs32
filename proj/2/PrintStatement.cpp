// PrintStatement.cpp:
#include "PrintStatement.h"

PrintStatement::PrintStatement(char variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	char var = this->m_variableName;
	outf << state->getVariable(var) << std::endl;
	state->incrementCounter();
}
