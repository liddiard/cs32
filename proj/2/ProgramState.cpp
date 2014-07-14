#include <stdlib.h>
#include <iostream>
#include "ProgramState.h"
#include "globals.h"
using namespace std;

/* PUBLIC METHODS */

ProgramState::ProgramState(int numLines)
{
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        Variable to_add;
        to_add.name = this->arrayPositionToChar(i);
        to_add.value = 0;
        this->variables[i] = to_add;
    }
    this->m_numLines = numLines;
    this->program_counter = 1; // point of entry is line 1
    this->gosub_returns = new Stack<int>;
}

int ProgramState::getCounter()
{
    return this->program_counter;
}

void ProgramState::setCounter(int line, ostream &outf)
{
    if (this->isInBounds(line))
        this->program_counter = line;
    else
    {
        outf << endl << "Illegal jump instruction" << endl;
        exit(1);
    }
}

void ProgramState::incrementCounter()
{
    this->program_counter++;
}

int ProgramState::getVariable(char var) const
{
    int array_pos = this->charToArrayPosition(var);
    // CAUTION: does not check if char passed is a valid position in the variables array
    return this->variables[array_pos].value;
}

bool ProgramState::setVariable(char var, int value)
{
    int array_pos = this->charToArrayPosition(var);
    if (this->arrayPositionInBounds(array_pos))
    {
        this->variables[array_pos].value = value;
        return true;
    } else return false;
}


/* PRIVATE METHODS */

bool ProgramState::isInBounds(int line) const
{
    return (line > 0 && line <= this->m_numLines);
}


int ProgramState::charToArrayPosition(char c) const
{
    return (int)(c - CAPITAL_A_OFFSET);
}

char ProgramState::arrayPositionToChar(int i) const
{
    return (char)(CAPITAL_A_OFFSET + i);
}

bool ProgramState::arrayPositionInBounds(int pos) const
{
    return (pos >= 0 && pos < ALPHABET_LENGTH);
}
