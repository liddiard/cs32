#include <string>
#include "Multiset.h"

Multiset::Multiset() 
{
    this->dict_size = 0;   
}

bool Multiset::empty() const
{
    if (this->dict_size > 0)
        return false;
    else 
        return true; 
}

int Multiset::size() const
{
    int count = 0;
    for (int i = 0; i < this->dict_size; i++)
    {
        count += this->dict[i].count;
    }
    return count;
}

int Multiset::uniqueSize() const
{
    return this->dict_size;
}

bool Multiset::insert(const ItemType& value)
{
    if (this->dict_size < DEFAULT_MAX_ITEMS) // if there's room in the multiset
    {
        int index = this->find(value);
        if (index != -1) // item was found
        {
            this->dict[index].count++; // perform an update
            return true;
        }
        else // if we get here, the value wasn't in the multiset already
        {
            // TODO: figure out if this line is needed: this->dict[dict_size] = Item; // perform an insertion
            this->dict[dict_size].count = 1;
            this->dict[dict_size].name = value;
            this->dict_size++;
            return true;
        }
    }
    else return false;
}

int Multiset::erase(const ItemType& value)
{
    int index = this->find(value);
    if (index != -1) // the item was found
    {
        if (this->dict[index].count > 1)
            this->dict[index].count--;
        else // there's only one item left of the item type
            this->remove(index);
        return 1;
    }
    else
        return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    int count = 0;
    int index = this->find(value);
    if (index != -1) // the item was found
    {
        count = this->dict[index].count;
        this->remove(index);
    }
    else return 0;
}

bool Multiset::contains(const ItemType& value) const
{
    if (this->find(value) != -1)
        return true;
    else
        return false;
}

int Multiset::count(const ItemType& value) const
{
    int index = this->find(value);
    if (index == -1) // item was not found
        return 0;
    return dict[index].count;
}

int Multiset::get(int i, ItemType& value)
{
    if (i >= 0 && i < this->dict_size)
    {
        value = this->dict[i].name;
        return this->dict[i].count;
    }
    else return 0; // index requested is out of bounds
}

void Multiset::swap(Multiset& other)
{
    
}

int Multiset::find(const ItemType& value) const
{
    for (int i = 0; i < this->dict_size; i++)
    {
        if (this->dict[i].name == value)
            return i;
    }
    return -1; // not found
}

bool Multiset::remove(int index)
{
    if (index >= 0 && index < this->dict_size)
    {
        for (int i = index; i < this->dict_size-1; i++)
        // shift all following elements over
        {
            this->dict[i] = this->dict[i+1];
        }
        this->dict_size--;
        return true;
    }
    else return false;
}
