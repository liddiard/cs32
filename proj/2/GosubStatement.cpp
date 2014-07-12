#include "GosubStatement.h"
#include <iostream>
using namespace std;

GosubStatement::GosubStatement(int line)
    : m_line( line )
{}

void GosubStatement::execute(ProgramState * state, ostream &outf)
{
    int line = this->m_line;
    state->gosub_returns->push(state->getCounter()+1);
    state->setCounter(line);
}
