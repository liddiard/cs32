#include <string>
#include <stack>
#include <iostream>

const int NUM_SYMBOLS = 3;

struct Pair
{
    char opening;
    char closing;
    Pair(char o, char c) : opening(o), closing(c) {};
};

Pair parens = Pair('(', ')');
Pair brackets = Pair('[', ']');
Pair braces = Pair('{', '}');

const char opening_symbol[NUM_SYMBOLS] = {parens.opening, brackets.opening, braces.opening};
const char closing_symbol[NUM_SYMBOLS] = {parens.closing, brackets.closing, braces.closing};

bool contains(const char arr[], char find)
{
    for (int i = 0; i < NUM_SYMBOLS; i++)
    {
        if (arr[i] == find)
            return true;
    }
    return false;
}

bool balanced(std::string expr)
{
    std::stack<char> symbols;
    for (int i = 0; i < expr.size(); i++)
    {
        if (contains(opening_symbol, expr[i]))
        {
            switch(expr[i])
            {
                case '(':
                    symbols.push(')');
                    break;
                case '[':
                    symbols.push(']');
                    break;
                case '{':
                    symbols.push('}');
                    break;
            }
        }
        else if (contains(closing_symbol, expr[i]))
        {
            if (symbols.empty()) return false; // unmatched closing symbol
            if (expr[i] != symbols.top()) return false; // improperly nested
            symbols.pop();
        }
    }
    return (symbols.empty()); // if symbols not empty, unmatched opening symbol
}

int main()
{
    std::cout << balanced("([)]") << std::endl;
}
