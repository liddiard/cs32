#include "ProgramState.h"

ProgramState::ProgramState(int numLines)
{
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        Variable to_add;
        to_add.name = (char)(65+i);
        to_add.value = 0;
        this->variables[i] = to_add;
    }
    this->m_numLines = numLines;
}

void ProgramState::incrementCounter()
{
    this->program_counter++; 
}

void ProgramState::setCounter(int line)
{
    this->program_counter = line;
}
