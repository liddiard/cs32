#ifndef LINKED_LIST_INCLUDED
#define LINKED_LIST_INCLUDED

struct Element
{
    string data;
    Element * next;
}

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
        Element * front;
};

List::List(): front(nullptr)
{
}

bool List::add(string s)
{
    if (front == nullptr)
    {
        front = new Element;
        front->data = s;
        front->next = nullptr;
        return true;
    }
    Element * cur = front;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    cur->next = new Element;
    cur->next->data = s;
    cur->next->next = nullptr;
    return true;
}

bool List::contains(string q)
{
    Element * cur = front;
    if (!front)
        return false;
    while (cur != nullptr) {
        if (cur->data == q)
            return true;
        else
            cur = cur->next;
    }
    return false;
}


#endif
