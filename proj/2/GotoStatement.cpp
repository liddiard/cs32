#include <stdlib.h>
#include <iostream>
#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int line)
    : m_line ( line )
{}

void GotoStatement::execute(ProgramState * state, ostream &outf)
{
    if (state->isInBounds(this->m_line))
        state->setCounter(this->m_line);
    else
    {
        cerr << "Illegal jump instruction";
        exit(1);
    }
}
