#include "BinarySearchTree.h"

struct BinarySearchTree::Node {
    Key key;
    Item item;
    Node* leftChild;
    Node* rightChild;
    Node(Key, Item);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::Node::Node(Key key, Item item) {
    this->key = key;
    this->item = item;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

void BinarySearchTree::insert(Key key, Item item) {
    if (root == nullptr) {
        root = new Node(key, item);
        } else {
        insertRecursive(key, item, root);
    }
};

void BinarySearchTree::insertRecursive(Key key, Item item, Node* nodePtr) {
    if (nodePtr->key == key) {
        nodePtr->item = item;
    } else {
        Node* & child = nodePtr->key > key ? nodePtr->leftChild : nodePtr->rightChild;
        if (child!=nullptr) {
            insertRecursive(key, item, child); 
        }   else  {
            child = new Node(key, item);
        }
    }
}
 
BinarySearchTree::Item* BinarySearchTree::lookup(Key key){
    	return lookupRecursive(key, root);
}

BinarySearchTree::Item* BinarySearchTree::lookupRecursive(Key key, Node* nodePtr){
    if (nodePtr == nullptr) {
      return nullptr;
    } else if (nodePtr->key > key) {
      return lookupRecursive(key, nodePtr->leftChild);  
    } else if (nodePtr->key < key) {
      return lookupRecursive(key, nodePtr->rightChild);  
    } else {
      return &nodePtr->item;
    }
}

void BinarySearchTree::preOrder(pairconsumer con) {
    if (root!=nullptr) preOrderRecursive(con,root,0);
}

void BinarySearchTree::preOrderRecursive(pairconsumer con, Node* nodePtr, int gen) {
    con(nodePtr, gen);
    if (nodePtr->leftChild!=nullptr) preOrderRecursive(con, nodePtr->leftChild, gen+1);
    else con(nullptr, gen+1);
    if (nodePtr->rightChild!=nullptr) preOrderRecursive(con, nodePtr->rightChild, gen+1);
    else con(nullptr, gen+1);
}

void BinarySearchTree::inOrder(consumer con) {
    if (root!=nullptr) {
        inOrderRecursive(con,root);
    }
}

void BinarySearchTree::inOrderRecursive(consumer con, Node* nodePtr) {
    if (nodePtr->leftChild!=nullptr) inOrderRecursive(con, nodePtr->leftChild);
    con(nodePtr);
    if (nodePtr->rightChild!=nullptr) inOrderRecursive(con, nodePtr->rightChild);
}

void BinarySearchTree::postOrder(consumer con) {
    if (root!=nullptr) postOrderRecursive(con,root);
}

void BinarySearchTree::postOrderRecursive(consumer con, Node* nodePtr) {
    if (nodePtr->leftChild!=nullptr) postOrderRecursive(con, nodePtr->leftChild);
    if (nodePtr->rightChild!=nullptr) postOrderRecursive(con, nodePtr->rightChild);
    con(nodePtr);
}

void BinarySearchTree::displayEntries()
{
    this->inOrder([](BinarySearchTree::Node* n) -> void {
        std::cout << n->key << ": " << n->item << std::endl;
    }
                 );
}

void BinarySearchTree::displayTree()
{
    this->preOrder([](Node* n,int gen) -> void {
        std::string out = std::to_string(gen)+"| ";
        for(int i=0; i<gen;i++) out += "      ";
        if (n== nullptr) std::cout << out + "*"<<std::endl;
        else std::cout << out + std::to_string(n->key) + ": " + n->item <<std::endl;
    }
    );
    
}

void BinarySearchTree::remove(BinarySearchTree::Key key)
{
    if (root!=nullptr) removeRecursive(key,root);
}

void BinarySearchTree::removeRecursive(Key key, Node* &nodePtr) {
    if (nodePtr->key > key) {
        if (nodePtr->leftChild != nullptr && nodePtr->leftChild->key == key) {
            delete nodePtr->leftChild;
            nodePtr->leftChild = nullptr;
        }
        else removeRecursive(key, nodePtr->leftChild);
    } else if (nodePtr->key < key) {
        if (nodePtr->rightChild != nullptr &&nodePtr->rightChild->key == key ) {
            delete nodePtr->rightChild;
            nodePtr->rightChild = nullptr;
        }
        else removeRecursive(key, nodePtr->rightChild);
    } else {
        delete nodePtr;
        nodePtr = nullptr;
    }    
}


std::ostream &operator<<(std::ostream & os, const BinarySearchTree & bst){
    BinarySearchTree tree = bst;
    tree.inOrder([&](BinarySearchTree::Node* n) -> void {
        if (n != nullptr) {
            os << std::to_string(n->key)+": " + n->item+", ";
        }
    });
    return os;
}
