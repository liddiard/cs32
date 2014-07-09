#include <string>
#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack<string>* t_stack = new Stack<string>;
    t_stack->push("foo");
    t_stack->push("bar");
    if (!t_stack->empty()) cout << t_stack->top();   
    t_stack->pop();
    if (!t_stack->empty()) cout << t_stack->top();   
    t_stack->pop();
    if (!t_stack->empty()) cout << t_stack->top();   
}
