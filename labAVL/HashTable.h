#ifndef _DRH_HASHT
#define _DRH_HASHT
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>
template <class K, class I>
class HashTable {
    public:
        using Key = K;
        using Item = I;
        using KvPair = std::pair<K,I>;
        using Bucket = std::vector<KvPair>;
        std::vector<Bucket> vec;

//        HashTable();

//     void insert(Key, Item);
        // Item* lookup(Key);
        // void remove(Key);
    // private:
//        static unsigned int hash(const K &);//Only hashes, does not modulo

    unsigned int hash(const K & key) {
        return std::hash<K>{}(key)%vec.size();
    }

    HashTable() {
        vec.resize(100);
    }

    void insert(K key, I item) {
        Bucket &bucket = vec[hash(key)];
        bool keyPresent = std::any_of(bucket.begin(),bucket.end(), [key](KvPair p)-> bool { return p.first == key;});
        if (keyPresent) {
            auto ip = std::find_if(bucket.begin(), bucket.end(), [key](KvPair p)-> bool { return p.first == key;});
            ip->second = item;
        } else {
            bucket.push_back(KvPair(key, item));
        }
    }
};

#endif