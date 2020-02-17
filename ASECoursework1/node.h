#ifndef ASECOURSEWORK_NODE_H
#define ASECOURSEWORK_NODE_H

namespace Containers {
    template<class K, class I>
    class Node{
    public:
        K key;
        I item;
        Node(K k, I i);
        Node(const Node &);
        Node<K,I> *next;
    };

    template<class K, class I>
    Node<K,I>::Node(K k, I i) {
        key = k;
        item = i;
        next = nullptr;
    }

    template<class K, class I>
    Node<K, I>::Node(const Node<K,I> & old) {
        key = old.key;
        item = old.item;
        next = nullptr;
    }
}


#endif //ASECOURSEWORK_NODE_H
