#include <string>
#include "IfStatement.h"
using namespace std;

IfStatement::IfStatement(char var, string op, int compare, int dest)
    : m_variableName( var ), m_op ( op ), m_comparison ( compare ), 
      m_destination( dest )
{}

void IfStatement::execute(ProgramState * state, ostream &outf)
{
    int val = state->getVariable(this->m_variableName);
    int comparison = this->m_comparison;
    bool statement_is_true = this->checkCondition(val, this->m_op, comparison);
    if (statement_is_true)
    	state->setCounter(this->m_destination);
    else state->incrementCounter();
}

bool IfStatement::checkCondition(int first_operand, string op, int second_operand)
{
	if (op == "=")
		return (first_operand == second_operand);
	else if (op == "<>")
		return (first_operand != second_operand);
	else if (op == ">")
		return (first_operand > second_operand);
	else if (op == "<")
		return (first_operand < second_operand);
	else if (op == ">=")
		return (first_operand >= second_operand);
	else if (op == "<=")
		return (first_operand <= second_operand);
	else
		return false;
	// TODO: default case for invalid operator
}