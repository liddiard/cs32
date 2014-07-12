#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int line)
    : m_line ( line )
{}

void GotoStatement::execute(ProgramState * state, ostream &outf)
{
    state->setCounter(this->m_line);
}
