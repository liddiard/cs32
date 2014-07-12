#include <stdlib.h>
#include <iostream>
#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement(){}

void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
    Stack<int>* gosub_returns = state->gosub_returns;
    if (gosub_returns->empty()) // RETURN was encountered outside subroutine
    {
        cout << "Illegal return statement";
        exit(1);
    }
        int return_line = gosub_returns->top();
        gosub_returns->pop();
        state->setCounter(return_line);
}
