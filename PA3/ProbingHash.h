#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
	int numOfElements = 0;			// Stores the number of elements in the hash table
	vector<pair<pair<K, V>, EntryState>> table; // The actual table that stores lists that hold pairs

public:
    ProbingHash(int n = 11) {
		table.resize(findNextPrime(n) - 1, pair<pair<K, V>, EntryState>());
	}

    ~ProbingHash() {
        this->clear();
    }

    int size() {
		return numOfElements;
	}

    V operator[](const K& key) {
		int hashNum = hash(key);
		int originalHashNum = hashNum;
		bool success = false;
		while (!success)
		{
			if (table[hashNum].second == VALID)
			{
				success = true;
				return table[hashNum].first.second;
			}
			else
			{
				if (hashNum < bucket_count())
				{
					hashNum++;
				}
				else
				{
					hashNum = 0;
				}
				if (hashNum == originalHashNum) {
					success = false;
				}
			}
		}
		return -1;
	}

    bool insert(const std::pair<K, V>& pair) {
		int hashNum = hash(pair.first);
		bool success = false;
		while (!success) {
			if (table[hashNum].second != VALID) {
				table[hashNum].first.first = pair.first;
				table[hashNum].first.second = pair.second;
				table[hashNum].second = VALID;
				numOfElements++;
				success = true;
			}
			else {
				if (hashNum < bucket_count()) {
					hashNum++;
				}
				else {
					hashNum = 0;
				}
			}
		}

		// Checks if it should rehash
		if (load_factor() > 0.75)
		{
			rehash();
		}

		return success;
    }

    void erase(const K& key) {
		int hashNum = hash(key);
		int originalHashNum = hashNum;
		bool success = false;
		while (!success)
		{
			if (table[hashNum].second != VALID)
			{
				success = true;
				table[hashNum].second = DELETED;
				numOfElements--;
			}
			else
			{
				if (hashNum < bucket_count())
				{
					hashNum++;
				}
				else
				{
					hashNum = 0;
				}
				if (hashNum == originalHashNum)
				{
					success = false;
				}
			}
		}
	}

    void clear() {
		table.clear();
    }

    int bucket_count() {
		return table.size();
	}

    float load_factor() {
		float j = numOfElements;
		float i = table.size();
		float x = j / i;
		return x;
	}

	void rehash()
	{
		// Creates a vector of all the elements in the table
		vector<pair<K, V>> holding;
		int j = table.size();
		for (int i = 0; i < j; i++)
		{
			if (table[i].second == VALID) {
				pair<K, V> tempPair;
				tempPair.first = table[i].first.first;
				tempPair.second = table[i].first.second;
				holding.push_back(tempPair); // Put the pair into the holding vector
			}
		}

		int oldSize = bucket_count();
		// Clear out the current table
		clear();
		numOfElements = 0;

		// Resize table to next prime number
		table.resize(findNextPrime(oldSize * 2), pair<pair<K, V>, EntryState>());

		// Insert elements back into table
		for (int i = 0; i < holding.size(); i++)
		{
			insert(holding[i]);
		}
	}

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
		return (key % (bucket_count() - 1));
	}
    
};

#endif //__PROBING_HASH_H
