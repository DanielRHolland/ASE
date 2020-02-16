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
        Dictionary(const Dictionary &);
        ~Dictionary();

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
        for (Node<K,I> *n = first; n != nullptr; n = n->next ) {
            if (n->key == k) {
                n->item = i;
                return true;
            }
        }
        Node<K,I> *newNode = new Node<K,I>(k,i);
        newNode->next = first;
        first = newNode;
        return false;
    }

    template<class K, class I>
    I* Dictionary<K, I>::lookup(Key k) {
        for (Node<K,I> *n = first; n != nullptr; n = n->next ) {
            if (n->key == k) {
                return &n->item;
            }
        }
        return nullptr;
    }

    template<class K, class I>
    bool Dictionary<K, I>::remove(Key k) {
        for (Node<K,I> *n = first, *parent = nullptr; n != nullptr ; parent = n, n = n->next ) {
            if (n->key == k) {
                if (parent == nullptr) {
                    first = n->next;
                } else {
                    parent->next = n->next;
                }
                delete n;
                return true;
            }
        }
        return false;
    }

    template<class K, class I>
    int Dictionary<K, I>::removeIf(Predicate p) {
        int numberRemoved = 0;
        for (Node<K,I> *n = first, *parent = nullptr; n != nullptr ; ) {
            if (p(n->key)) {
                Node<K,I> *&ptrToNext = parent == nullptr ? first : parent->next;
                ptrToNext = n->next;
                delete n;
                n = ptrToNext;
                numberRemoved++;
            } else {
                parent = n;
                n = n->next;
            }
        }
        return numberRemoved;
    }

    template<class K, class I>
    Dictionary<K, I>::~Dictionary() {
        for (Node<K,I> *n = first, *toRemove; n != nullptr;) {
            toRemove = n;
            n = n->next;
            delete toRemove;
        }
    }

    template<class K, class I>
    Dictionary<K, I>::Dictionary(const Dictionary & old) {
        first = new Node<K,I>(*old.first);
    }
}


#endif //ASECOURSEWORK_DICTIONARY_H

/*
 * Questions:
 * - return value of removeIf?
 * - proper-ness of for loops as whiles + declarations?
 * - any need to store in order?
 * - copy should preserve structure?
 * - Node recursive copy constructor Vs deepcopy function in dictionary
*/