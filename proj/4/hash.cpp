#include "hash.h"
using namespace std;

HashTable::HashTable(int items) : m_nBuckets(items / MAX_LOAD_FACTOR) 
{	
	std::vector<int>::size_type size = m_nBuckets;
	m_storage.reserve(size);

	for (int i = 0; i < m_nBuckets; i++)
	{
		m_storage.push_back(Bucket());
	}
}

int HashTable::hash(string val)
{
	int sum = 0;
    for (string::size_type i = 0; i < val.length(); i++)
    {
        sum += val[i];
    }
    return sum % m_nBuckets;
}

bool HashTable::insert(string val)
{
	int bucket = this->hash(val);

	for (int tries = 0; tries < m_nBuckets; tries++)
	{
		if (!m_storage[bucket].used)
		{
			m_storage[bucket].val = val;
			m_storage[bucket].used = true;
			return true; // value inserted successfully
		}
		bucket = ++bucket % m_nBuckets;
	}
	return false; // No room in hash table!
}

bool HashTable::find(string val)
{
	int bucket = this->hash(val);

	for (int tries = 0; tries < m_nBuckets; tries++)
	{
		if (!m_storage[bucket].used)
			return false; // there's nothing here
		if (m_storage[bucket].val == val)
			return true; // value found
		bucket = ++bucket % m_nBuckets;
	}
	return false; // not found
}