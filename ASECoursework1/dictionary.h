#ifndef ASECOURSEWORK_DICTIONARY_H
#define ASECOURSEWORK_DICTIONARY_H

#include <functional>
#include "node.h"


namespace Containers {
    template <class K, class I>
    class Dictionary {
    public:
        using Key = K;// ... must support at least std::string
        using Item = I;// ... must support at least std::string
        typedef std::function<bool(Key)> Predicate;
        Dictionary();

        bool insert(Key, Item);

        Item *lookup(Key);

        bool remove(Key);

        int removeIf(Predicate);

    private:
        Node<Key,Item> *first;

    };

    template <class K, class I>
    Dictionary<K,I>::Dictionary(){
        first = nullptr;
    }

    template<class K, class I>
    bool Dictionary<K, I>::insert(Key k, Item i) {
        if (first == nullptr) {
            first = new Node<K,I>(k,i);
            return false;
        } else if (first->key > k){
            Node<K,I> *newNode = new Node<K,I>(k,i);
            newNode->next = first;
            first = newNode;
            return false;
        } else if (first->key == k) {
            first->item = i;
            return true;
        } else {
            for (Node<K,I> *n = first;; n = n->next ) {
                if (n->next == nullptr) {
                    n->next = new Node<K, I>(k, i);
                    return false;
                } else if (n->next->key > k) {
                    Node<K,I> *newNode = new Node<K,I>(k,i);
                    newNode->next = n->next;
                    n->next = newNode;
                    return false;
                } else if (n->next->key == k) {
                    n->next->item = i;
                    return true;
                }
            }
        }
    }

    template<class K, class I>
    I* Dictionary<K, I>::lookup(Key k) {
        for (Node<K,I> *n = first; ; n = n->next ) {
            if (n == nullptr){
                return nullptr;
            } else if (n->key == k) {
                return &n->item;
            }
        }
    }

    template<class K, class I>
    bool Dictionary<K, I>::remove(Key k) {
        for (Node<K,I> *n = first, *parent = nullptr; n != nullptr ; parent = n, n = n->next ) {
            if (n->key == k) {
                if (parent == nullptr) {
                    first = n->next;
                    delete n;
                } else {
                    parent->next = n->next;
                    delete n;
                }
                return true;
            }
        }
        return false;
    }

    template<class K, class I>
    int Dictionary<K, I>::removeIf(Predicate) {
        return 0;
    }
}


#endif //ASECOURSEWORK_DICTIONARY_H
