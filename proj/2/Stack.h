#ifndef STACK_INCLUDED
#define STACK_INCLUDED

template <typename T>
struct StackNode
{
    T data;
    StackNode* next;
    StackNode (T data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T>
class Stack
{
public:
	Stack();
	void push(T x);
	void pop();
	T top() const;
	bool empty() const;

private:
	StackNode<T> * head;
};

template <typename T>
Stack<T>::Stack()
{
    this->head = nullptr;
}

template <typename T>
void Stack<T>::push(T x)
{
    StackNode<T>* to_add = new StackNode<T>(x);
    if (this->head == nullptr)
        this->head = to_add;
    else
    {
        to_add->next = this->head;
        this->head = to_add;
    }
}

template <typename T>
void Stack<T>::pop()
{
    if (this->head == nullptr) // the stack is empty
        return;
    else
    {
        StackNode<T>* new_head = this->head->next;
        delete this->head;
        this->head = new_head;
    }
}

template <typename T>
T Stack<T>::top() const
{
    return this->head->data; // WARNING: will segfault if stack is empty`
}

template <typename T>
bool Stack<T>::empty() const
{
    return (this->head == nullptr);
}

#endif
