#include "stack.h"

Stack::Stack()
{
    this->head = nullptr;
}

void Stack::push(T x)
{
    to_add = new StackNode(x);
    if (this->head == nullptr)
        this->head = to_add;
    else
    {
        to_add.next = this->head;
        this->head = to_add;
    }
}

void Stack::pop()
{
    if (this->head == nullptr) // the stack is empty
        return;
    else
    {
        StackNode* new_head = this->head.next;
        delete this->head;
        this->head = new_head;
    }
}

T Stack::top() const
{
    return *(this->head);
}

bool Stack::empty() const
{
    return (this->head == nullptr);
}
