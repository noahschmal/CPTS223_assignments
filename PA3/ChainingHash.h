/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <iterator>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
	int numOfElements = 0; // Stores the number of elements in the hash table
	vector<list<pair<K, V>>> table; // The actual table that stores lists that hold pairs

public:
	// Constructor
    ChainingHash(int n = 11) {
		table.resize(findNextPrime(n) - 1, list<pair<K, V>>());
    }

	// Destructor
    ~ChainingHash() {
        this->clear();
    }

	// Returns the number of elements in the vetor
    int size() {
        return numOfElements;
    }

	// Search function
    V operator[](const K& key) {
		int hashNum = hash(key);
		typename list<pair<K, V>>::iterator it;

		for (it = table[hashNum].begin(); it != table[hashNum].end(); it++)
		{
			if(it->first == key)
				return it->second;
		}
		return -1;
    }

	// Inserts into the hash table
    bool insert(const std::pair<K, V>& pair) {
		int hashNum = hash(pair.first); // Gets the hash number
		table[hashNum].push_back(pair); // Pushes the pair into the appropriate list
		numOfElements++; // Increases counter

		// Checks if it should rehash
		if (load_factor() > 0.75) {
			rehash();
		}
        return true;
    }

	// Removes from the hash table
    void erase(const K& key) {
		int hashNum = hash(key);
		typename list<pair<K, V>>::iterator it;

		for (it = table[hashNum].begin(); it != table[hashNum].end(); it++)
		{
			if (it->first == key) {
				table[hashNum].erase(it);
				numOfElements--;
				return;
			}
		}
	}

	// Clears out the hash table
    void clear() {
		for (int i = 0; i < table.size(); i++) {
			table[i].clear(); // Clears each list in the vector
		}
		table.clear(); // Clears the vector
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

	// Rehashes the table
	/*void rehash() {
		table.resize(findNextPrime(bucket_count() + 2), list<pair<K, V>>());

		// Go through each list in the vector and reinsert the pair into the list
		int j = table.size();
		for (int i = 0; i < j; i++)
		{
			list<pair<K, V>> tempList;
			typename list<pair<K, V>>::iterator it;
			for (it = table[i].begin(); it != table[i].end(); it++)
			{
				pair<K, V> tempPair;
				tempPair.first = it->first;
				tempPair.second = it->second;
				tempList.push_back(tempPair);
			}
			table[i].clear();
			table[i] = tempList;
		}
	}*/


	void rehash() {
		// Creates a vector of all the elements in the table
		vector<pair<K, V>> holding;
		int j = table.size();
		for (int i = 0; i < j; i++) {
			typename list<pair<K, V>>::iterator it;
			for (it = table[i].begin(); it != table[i].end(); it++)
			{
				pair<K, V> tempPair;
				tempPair.first = it->first;
				tempPair.second = it->second;
				holding.push_back(tempPair); // Put the pair into the holding vector
			}
		}

		int oldSize = bucket_count();
		// Clear out the current table
		clear();
		numOfElements = 0;

		// Resize table to next prime number
		table.resize(findNextPrime(oldSize * 2), list<pair<K, V>>());

		// Insert elements back into table
		for (int i = 0; i < holding.size(); i++) {
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

	// Returns the hash value
    int hash(const K& key) {
        return (key % (bucket_count() - 1));       
    }

};

#endif //__CHAINING_HASH_H
