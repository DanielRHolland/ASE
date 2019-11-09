#ifndef _DRH_BST
#define _DRH_BST
#include <string>
#include <functional>
#include <iostream>
#include <algorithm>
#include <cassert>

class BinarySearchTree {
   friend std::ostream &operator<<(std::ostream &, const BinarySearchTree &);
    public:
        using Key = int;
        using Item = std::string;
        void insert(Key, Item); 
        Item* lookup(Key);
        BinarySearchTree();
        void displayEntries();
        void displayTree();
        void remove(Key);
        void rotateWholeTreeRight();
        void rotateWholeTreeLeft();
        void setTreeBalance();
        bool rebalanceRoot();
        // void 

    private:
        struct Node;
        typedef std::function< void(Node*) > consumer;
        typedef std::function< void(Node*,int) > pairconsumer;
        Node* root;
        void preOrder(pairconsumer);
        void inOrder(consumer);
        void postOrder(consumer);
        static bool insertRecursive(Key, Item, Node*);
        static Item* lookupRecursive(Key, Node*);
        static void preOrderRecursive(pairconsumer, Node*,int);
        static void inOrderRecursive(consumer, Node*);
        static void postOrderRecursive(consumer, Node*);
        void removeRecursive(Key, Node*&);
        static Node* detachMinimumNode(Node* &);
        static void rotateRight(Node* &);
        static void rotateLeft(Node* &);
        static int setBalanceRecursive(Node*);
        static bool rebalance(Node* &);
};

std::ostream &operator<<(std::ostream &, const BinarySearchTree &);
#endif
