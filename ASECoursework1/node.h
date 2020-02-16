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
        Node(Node &&);
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
        next = old.next == nullptr ? nullptr : new Node(*old.next);
    }

    template<class K, class I>
    Node<K, I>::Node(Node && original) {
        key = std::move(original.key);
        item = std::move(original.item);
        next = original.next == nullptr ? nullptr : std::move(original.next);
    }
}


#endif //ASECOURSEWORK_NODE_H
