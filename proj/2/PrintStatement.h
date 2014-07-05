
#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class PrintStatement: public Statement
{
private:
	char m_variableName;
	
public:
	PrintStatement(char variableName);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

