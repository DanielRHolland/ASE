#ifndef ASECOURSEWORK_NODE_H
#define ASECOURSEWORK_NODE_H

namespace Containers {
    template<class K, class I>
    class Node{
    public:
        K key;
        I item;
        Node(K k, I i);
        Node<K,I> *next;
    };

    template<class K, class I>
    Node<K,I>::Node(K k, I i) {
        key = k;
        item = i;
        next = nullptr;
    }
}


#endif //ASECOURSEWORK_NODE_H
