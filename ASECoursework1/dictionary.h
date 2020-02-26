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
        Dictionary(Dictionary&&) noexcept;
        ~Dictionary();
        bool insert(Key, Item);
        Item *lookup(Key);
        bool remove(Key);
        int removeIf(Predicate);
        Dictionary & operator=(const Dictionary &);
        Dictionary & operator=(Dictionary&& other) noexcept;


    private:
        Node<Key,Item> *first;
        void removeNodes();
        Node<Key,Item>* copyNodes(Node<Key, Item> *);
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
        removeNodes();
    }

    template<class K, class I>
    Dictionary<K, I>::Dictionary(const Dictionary & original) {
        first = copyNodes(original.first);
    }

    template<class K, class I>
    Dictionary<K,I> &Dictionary<K, I>::operator=(const Dictionary & original ) {
        removeNodes();
        first = copyNodes(original.first);
        return *this;
    }

    template<class K, class I>
    void Dictionary<K, I>::removeNodes() {
        for (Node<K,I> *toRemove = first, *n = first; toRemove != nullptr; toRemove = n) {
            n = n->next;
            delete toRemove;
        }
    }

    template<class K, class I>
    Dictionary<K, I>::Dictionary(Dictionary && other) noexcept {
        first = other.first;
        other.first = nullptr;
    }

    template<class K, class I>
    Dictionary<K,I> &Dictionary<K, I>::operator=(Dictionary &&other) noexcept {
        first = other.first;
        other.first = nullptr;
        return *this;
    }

    template<class K, class I>
    Node<K,I>* Dictionary<K, I>::copyNodes(Node<K, I> *old) {
        if (old != nullptr) {
            Node<K, I> *front = new Node<K, I>(*old);
            for (Node<K, I> *n = front; old->next != nullptr; old = old->next, n = n->next) {
                n->next = new Node<K, I>(*old->next);
            }
            return front;
        } else {
            return nullptr;
        }
    }
}


#endif //ASECOURSEWORK_DICTIONARY_H

