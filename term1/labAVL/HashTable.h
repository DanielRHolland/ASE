#ifndef _DRH_HASHT
#define _DRH_HASHT
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>
template <class K, class I>
class HashTable {
    private:
        int count = 0;
        int loadFactorThreshhold;

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
        loadFactorThreshhold = 0.8;
    }

    void insert(K key, I item) {
        KvPair* kvPairPtr = lookupKvPair(key);
        if (kvPairPtr != nullptr) {
            kvPairPtr->second = item;
        } else {
            vec[hash(key)].push_back(KvPair(key, item));
            count++;
            if (loadFactor()>loadFactorThreshhold) resize();
        }
    }

    Item* lookup(K key) {
        Bucket &bucket = vec[hash(key)];
        KvPair* kvpPtr = lookupKvPair(key);
        return kvpPtr!= nullptr?&(kvpPtr->second): nullptr;
    }

     void remove(Key key) {
        if (lookupKvPair(key)!= nullptr) {
            Bucket &bucket = vec[hash(key)];
            bucket.erase(std::find_if(bucket.begin(), bucket.end(), [key](KvPair p)-> bool { return p.first == key;}));
            count--;
        }
    }

    private:
        KvPair* lookupKvPair(K key) {
            Bucket &bucket = vec[hash(key)];
            bool keyPresent = std::any_of(bucket.begin(),bucket.end(), [key](KvPair p)-> bool { return p.first == key;});
            if (keyPresent) {
                return &(std::find_if(bucket.begin(), bucket.end(), [key](KvPair p)-> bool { return p.first == key;})[0]);
            } else {
                return nullptr;
            }
        }

        void resize() {
//TODO implement
        }

public:
        double loadFactor() {
            return (double)count / (double)vec.size();
        }
};

#endif