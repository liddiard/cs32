#include <string>

using namespace std;

class LinkedList
{
    public:
        LinkedList();
    private:
        *LinkNode front;
}l

class LinkNode
{
    string data;
    LinkedNode* next;
};

LinkedList::LinkedList(): front(nullptr) {};

void LinkedList::add(string s)
{
    LinkNode* ln = new LinkNode;
    ln->data = s;
    ln->next = nullptr;
    if (front == nullptr)
    {
        front = ln;
        return;
    }
    LinkNode * cur = front;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    cur-> next = ln;
}

void LinkedList::contains(string s) const
{
    LinkedNode* cur = this->front;
    while (cur != nullptr)
    {
        if (cur->data == s)
            return true;
        cur = cur->next;
    }
    return false;
}

void LinkedList::removeFirst()
{
    if (front != nullptr)
    {
        LinkNode * d = front;
        front = front->next;
        delete d;
    }
}

void LinkedList::remove(string s)
{
    LinkNode * cur = front;
    if (cur == nullptr)
        return;
    else if (front->data == s)
    {
        removeFirst();
        return;
    }
    LinkNode * prev = front;
    LinkNode * cur = prev->next;
    // invariant (assumption of truth): cur = prev->next;
    while (cur != nullptr && cur -> data != s)
    {
        prev = cur;
        cur = prev->next;
    }
    if (cur == nullptr) return;
    prev-> next = cur->next;
    delete cur;
}

int main() {};
