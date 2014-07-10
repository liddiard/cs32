#include "ProgramState.h"
#include "utilities.cpp"

ProgramState::ProgramState(int numLines)
{
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        Variable to_add;
        to_add.name = array_position_to_char(i);
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

bool ProgramState::setVariable(char var, int value)
{
    int array_pos = char_to_array_position(var);
    if (array_position_in_bounds(array_pos))
    {
        this->variables[array_pos].value = value;
        return true;
    } else return false;
}
