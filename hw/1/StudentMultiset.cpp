#include <iostream>
#include "StudentMultiset.h"

StudentMultiset::StudentMultiset() {
    this->ids_size = 0;    
}

bool StudentMultiset::add(unsigned long id)
{
    bool id_preexisting = this->submissions.contains(id);
    if (this->submissions.insert(id)) // id was successfully inserted
    {
        if (!id_preexisting)
        {
            this->ids[ids_size] = id;
            ids_size++;
        } 
        return true;
    }
    else return false;
}

int StudentMultiset::size() const
{
    return this->submissions.size();
}

void StudentMultiset::print() const
{
    for (int i = 0; i < ids_size; i++)
    {
        std::cout << this->ids[i] << std::endl; 
    }
}
