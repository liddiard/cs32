#ifndef HASH_INCLUDED
#define HASH_INCLUDED

#include <string>
#include <vector>

const float MAX_LOAD_FACTOR = 0.5;

struct Bucket
{
	std::string val;
	bool used;

	Bucket() : val(""), used(false) {}
};

// hash table for hashing strings
class HashTable
{
public:
	HashTable(int buckets);
	bool insert(std::string val);
	bool find(std::string val);

private:
	int hash(std::string val);
	int m_nBuckets;
	std::vector<Bucket> m_storage;
};

#endif // HASH_INCLUDED