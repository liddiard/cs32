#include "newMultiset.h"

Multiset::Multiset() 
{
    this->dict_size = 0;   
    this->dict = new Item*[DEFAULT_MAX_ITEMS];
    this->max_items = DEFAULT_MAX_ITEMS;
}

Multiset::Multiset(int max_items) 
{
    this->dict_size = 0;   
    this->dict = new Item*[max_items];
    this->max_items = max_items;
}

Multiset::~Multiset()
{
    delete[] this->dict;
}

Multiset::Multiset(const Multiset &source)
{
    this->max_items = source.max_items;
    this->dict_size = source.dict_size;
    for (int i = 0; i < source.dict_size; i++)
    {
        Item *to_add = new Item;
        to_add->name = source.dict[i]->name;
        to_add->count = source.dict[i]->count;
        this->dict[i] = to_add;
    }
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
        count += this->dict[i]->count;
    }
    return count;
}

int Multiset::uniqueSize() const
{
    return this->dict_size;
}

bool Multiset::insert(const ItemType& value)
{
    int index = this->find(value);
    if (index != -1) // item was found
    {
        this->dict[index]->count++; // perform an update
        return true;
    }
    else if (this->dict_size < this->max_items) // if there's room in the multiset
    {
        Item* insert = new Item;
        insert->name = value;
        insert->count = 1;
        this->dict[dict_size] = insert;
        this->dict_size++;
        return true;
    }
    else return false;
}

int Multiset::erase(const ItemType& value)
{
    int index = this->find(value);
    if (index != -1) // the item was found
    {
        if (this->dict[index]->count > 1)
            this->dict[index]->count--;
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
        count = this->dict[index]->count;
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
    return dict[index]->count;
}

int Multiset::get(int i, ItemType& value)
{
    if (i >= 0 && i < this->dict_size)
    {
        value = this->dict[i]->name;
        return this->dict[i]->count;
    }
    else return 0; // index requested is out of bounds
}

void Multiset::swap(Multiset& other)
{
    Item** tmp = new Item*[this->max_items]; // create a temporary array
    int tmp_size = this->dict_size;
    int tmp_max_items = this->max_items;
    for (int i = 0; i < this->dict_size; i++) // copy current items into tmp
    {
        tmp[i] = this->dict[i];
    }
    for (int i = 0; i < other.uniqueSize(); i++) // copy other's items into current
    {
        ItemType name;
        int count = other.get(i, name);
        Item *to_add = new Item;
        to_add->name = name;
        to_add->count = count;
        this->dict[i] = to_add;
    }
    this->dict_size = other.uniqueSize(); // update current's size
    this->max_items = other.max_items;
    for (int i = 0; i < tmp_size; i++)
    {
       other.dict[i] = tmp[i]; 
    }
    other.dict_size = tmp_size;
    other.max_items = tmp_max_items;
    delete[] tmp;
}

int Multiset::find(const ItemType& value) const
{
    for (int i = 0; i < this->dict_size; i++)
    {
        if (this->dict[i]->name == value)
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
