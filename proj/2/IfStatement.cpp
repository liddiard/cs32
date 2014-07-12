#include "IfStatement.h"
using namespace std;

IfStatement::IfStatement(char var, char op, int compare, int dest)
    : m_variableName( var ), m_op ( op ), m_comparison ( compare ), 
      m_destination( dest )
{}

void IfStatement::execute(ProgramState * state, ostream &outf)
{
    int val = state->getVariable(var);
    int comparison = this->m_comparison;
    statement_is_true = this->checkCondition(val, this->m_op, comparison);
    if (statement_is_true)
    	state->setCounter(this->m_destination);
    else state->incrementCounter();
}

bool IfStatement::checkCondition(int first_operand, char op, int second_operand)
{
	switch(op)
	{
		case '=':
			return (first_operand == second_operand);
		case '>':
			return (first_operand > second_operand);
		case '<':
			return (first_operand < second_operand);
		case '>=':
			return (first_operand >= second_operand);
		case '<=':
			return (first_operand <= second_operand);
	}
}