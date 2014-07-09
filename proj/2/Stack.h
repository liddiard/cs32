#ifndef STACK_INCLUDED
#define STACK_INCLUDED

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
    template <typename U>
    struct StackNode
    {
        U data;
        StackNode* next;
        StackNode (U data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

	StackNode<T> * head;
};

#endif

