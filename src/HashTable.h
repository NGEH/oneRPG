#pragma once

#include <vector>
#include <cinttypes>

template<typename t_key>
using HashFunction = uint32_t(*)(t_key&);

template<typename t_key, typename t_val>
struct HashTable {
	struct Bucket {
		t_key key;
		t_val val;

		Bucket* chain; //chaining
	};

	int size;
	std::vector<Bucket*> buckets;
	
	HashFunction<t_key> hash_func;

	HashTable(HashFunction<t_key> func, int size = 64) {
		this->size = size;
		buckets = std::vector<Bucket*>();
		buckets.resize(size);

		hash_func = func;
	}

	t_val& insert(t_key key, t_val val) {
		int bucket_index = hash_func(key) % size;
		Bucket* b = buckets[bucket_index];

		while (b && b->chain) {
			b = b->chain;
		}
		
		Bucket* temp = new Bucket();
		temp->key = key;
		temp->val = val;
		temp->chain = nullptr;

		if (b) {
			b->chain = temp;
		}
		else {
			buckets[bucket_index] = temp;
		}

		return temp->val;
	}


	t_val& get(t_key key) {
		int bucket_index = hash_func(key) % size;
		Bucket* b = buckets[bucket_index];

		while (b) {
			if (b->key == key) {
				return b->val;
			}
			if (b->chain) {
				b = b->chain;
			}
		}

		return insert(key, t_val());
	}

	t_val& operator[](t_key key) {
		return get(key);
	}

	bool exists(t_key key) {
		int bucket_index = hash_func(key) % buckets.size();
		Bucket* b = buckets[bucket_index];

		while (b) {
			if (b->key == key) {
				return true;
			}
			if (b->chain) {
				b = b->chain;
			}
		}
		
		return false;
	}
};