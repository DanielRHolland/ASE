#ifndef _DRH_BST
#define _DRH_BST
#include <string>
#include <functional>
#include <iostream>

template <class K, class I>
class BinarySearchTree {
   friend std::ostream &operator<<(std::ostream &, const BinarySearchTree &);
    public:
        using Key = K;
        using Item = I;
        void insert(Key, Item); 
        Item* lookup(Key);
        BinarySearchTree();
        void displayEntries();
        void displayTree();
        void remove(Key);
        void rotateWholeTreeRight();
        void rotateWholeTreeLeft();

    private:
        struct Node;
        typedef std::function< void(Node*) > consumer;
        typedef std::function< void(Node*,int) > pairconsumer;
        Node* root;
        void preOrder(pairconsumer);
        void inOrder(consumer);
        void postOrder(consumer);
        static void insertRecursive(Key, Item, Node*);
        static Item* lookupRecursive(Key, Node*);
        static void preOrderRecursive(pairconsumer, Node*,int);
        static void inOrderRecursive(consumer, Node*);
        static void postOrderRecursive(consumer, Node*);
        void removeRecursive(Key, Node*&);
        static Node* detachMinimumNode(Node* &);
        static void rotateRight(Node* &);
        static void rotateLeft(Node* &);
};

std::ostream &operator<<(std::ostream &, const BinarySearchTree &);
#endif
