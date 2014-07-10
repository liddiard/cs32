#include "globals.h"

const int CAPITAL_A_OFFSET = 65; // offset in ASCII of capital 'A' from zero

int char_to_array_position(char c)
{
    return (int)(c - CAPITAL_A_OFFSET);
}

char array_position_to_char(int i)
{
    return (char)(CAPITAL_A_OFFSET + i);
}

bool array_position_in_bounds(int pos)
{
    return (pos >= 0 && pos < ALPHABET_LENGTH);
}
