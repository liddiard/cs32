#ifndef STACK_INCLUDED
#define STACK_INCLUDED

template <typename T>
class StackNode;

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
	StackNode<T> * m_top;
};

#endif

