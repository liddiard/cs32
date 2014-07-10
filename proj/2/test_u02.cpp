#include <iostream>
#include "utilities.cpp"

using namespace std;

int main()
{
    cout << char_to_array_position('A');
    cout << array_position_to_char(0);
    cout << array_position_in_bounds(26);
}
