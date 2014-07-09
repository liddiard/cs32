#include <string>
#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack<string> t_stack;
    t_stack.push("hello");
    cout << t_stack.top();   
}
