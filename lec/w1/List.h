#ifndef LIST_INCLUDED
#define LIST_INCLUDED
#include <string>

const int MAXLEN = 100;

class List
{
    public:
        List();
        bool add(std::string s);
        int length() const; // method will not change any attr vars

    private:
        std::string elements[MAXLEN];
        int size;
};

List::List(): size(0) // initializer list
{
    size = 0;
}

bool List::add(std::string s)
{
    if (size == MAXLEN)
    {
        return false;
    }
    elements[size] = s;
    size++;
    return true;
}

int List::length() const // const required here for function signature
{
    return size;
}

#endif
