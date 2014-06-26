#ifndef LIST_INCLUDED
#define LIST_INCLUDED
#include <string>

const int MAXLEN = 100;

class List
{
    public:
        List();
        ~List();
        bool add(std::string s);
        int length() const; // method will not change any attr vars

    private:
        std::string * elements;
        int size, lenOfArray;
        void expandList();
};

List::List(): size(0), lenOfArray(START_LEN) // initializer list
{
    elements = new string [START_LEN];
}

List::~List():
{
    delete [] elements;
}

bool List::add(std::string s)
{
    if (size >= lenOfArray)
        expandList();
    elements[size] = s;
    size++;
    return true;
}

int List::length() const // const required here for function signature
{
    return size;
}

void List::expandList()
{
    const int FACTOR = 2;
    string * nl = new string[FACTOR * lenOfArray];
    for (int i=0; i < size; i++)
    {
        nl[i] = elements[i];
    }
    delete [] elements; // call with brackets because it's an array
    elements = nl;
    lenOfArray *= FACTOR;
}

#endif
