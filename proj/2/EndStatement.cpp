#include <stdlib.h>
#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement(){}

void EndStatement::execute(ProgramState * state, ostream &outf)
{
    exit(0);
}
