#include "BinarySearchTree.h"

struct BinarySearchTree::Node {
    Key key;
    Item item;
    Node* leftChild;
    Node* rightChild;
    Node(Key, Item);
};

BinarySearchTree<Key,Item>::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree<Key,Item>::Node::Node(Key key, Item item) {
    this->key = key;
    this->item = item;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}


void BinarySearchTree<Key,Item>::insert(Key key, Item item) {
    if (root == nullptr) {
        root = new Node(key, item);
        } else {
        insertRecursive(key, item, root);
    }
};


void BinarySearchTree<Key,Item>::insertRecursive(Key key, Item item, Node* nodePtr) {
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
 
BinarySearchTree<Key,Item>::Item* BinarySearchTree::lookup(Key key){
    	return lookupRecursive(key, root);
}

BinarySearchTree<Key,Item>::Item* BinarySearchTree::lookupRecursive(Key key, Node* nodePtr){
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

void BinarySearchTree<Key,Item>::preOrder(pairconsumer con) {
    if (root!=nullptr) preOrderRecursive(con,root,0);
}

void BinarySearchTree<Key,Item>::preOrderRecursive(pairconsumer con, Node* nodePtr, int gen) {
    con(nodePtr, gen);
    if (nodePtr->leftChild!=nullptr) preOrderRecursive(con, nodePtr->leftChild, gen+1);
    else con(nullptr, gen+1);
    if (nodePtr->rightChild!=nullptr) preOrderRecursive(con, nodePtr->rightChild, gen+1);
    else con(nullptr, gen+1);
}

void BinarySearchTree<Key,Item>::inOrder(consumer con) {
    if (root!=nullptr) {
        inOrderRecursive(con,root);
    }
}

void BinarySearchTree<Key,Item>::inOrderRecursive(consumer con, Node* nodePtr) {
    if (nodePtr->leftChild!=nullptr) inOrderRecursive(con, nodePtr->leftChild);
    con(nodePtr);
    if (nodePtr->rightChild!=nullptr) inOrderRecursive(con, nodePtr->rightChild);
}

void BinarySearchTree<Key,Item>::postOrder(consumer con) {
    if (root!=nullptr) postOrderRecursive(con,root);
}

void BinarySearchTree<Key,Item>::postOrderRecursive(consumer con, Node* nodePtr) {
    if (nodePtr->leftChild!=nullptr) postOrderRecursive(con, nodePtr->leftChild);
    if (nodePtr->rightChild!=nullptr) postOrderRecursive(con, nodePtr->rightChild);
    con(nodePtr);
}

void BinarySearchTree<Key,Item>::displayEntries()
{
    this->inOrder([](BinarySearchTree::Node* n) -> void {
        std::cout << n->key << ": " << n->item << std::endl;
    }
                 );
}

void BinarySearchTree<Key,Item>::displayTree()
{
    this->preOrder([](Node* n,int gen) -> void {
        std::string out = std::to_string(gen)+"| ";
        for(int i=0; i<gen;i++) out += "      ";
        if (n== nullptr) std::cout << out + "*"<<std::endl;
        else std::cout << out + std::to_string(n->key) + ": " + n->item <<std::endl;
    }
    );
    
}

void BinarySearchTree<Key,Item>::remove(BinarySearchTree::Key key)
{
    if (root!=nullptr) removeRecursive(key,root);
}

void BinarySearchTree<Key,Item>::removeRecursive(Key key, Node* &nodePtr) {
    if (nodePtr->key > key) {
        removeRecursive(key, nodePtr->leftChild);
    } else if (nodePtr->key < key){
        removeRecursive(key, nodePtr->rightChild);
    } else {
        //remove node at nodePtr
        if (nodePtr->rightChild != nullptr && nodePtr->leftChild != nullptr) {
            Node* detachedNode = detachMinimumNode(nodePtr->rightChild);
            detachedNode->leftChild = nodePtr->leftChild;
            detachedNode->rightChild = nodePtr->rightChild;
            nodePtr = detachedNode;
        } else if (nodePtr->rightChild != nullptr || nodePtr->leftChild != nullptr) {
            Node* childPtr = nodePtr->leftChild != nullptr ? nodePtr->leftChild : nodePtr->rightChild;
            delete nodePtr;
            nodePtr = childPtr;
        } else  {
            delete nodePtr;
            nodePtr = nullptr;
        }
    } 
}

BinarySearchTree<Key,Item>::Node* BinarySearchTree<Key,Item>::detachMinimumNode(Node* & nodePtr) {
    if (nodePtr->leftChild == nullptr) {
        Node* minimumNodePtr = nodePtr;
        nodePtr = nodePtr->rightChild;
        return minimumNodePtr;
    } else {
        return detachMinimumNode(nodePtr->leftChild);
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

void BinarySearchTree<Key,Item>::rotateRight(Node* & localRoot){
    assert(localroot!=nullptr);// if localroot==nullptr here, root of subtree is null, so cannot be rotated.
    Node* bPtr = localRoot;
    assert(bPtr->leftChild!=nullptr);// if lbPtr->leftChild==nullptr here, there is no left subtree, so no change caused by right rotation.
    localRoot = bPtr->leftChild;
    bPtr->leftChild = localRoot->rightChild;
    localRoot->rightChild = bPtr;
}

void BinarySearchTree<Key,Item>::rotateWholeTreeRight(){
    rotateRight(root);
}

void BinarySearchTree<Key,Item>::rotateLeft(Node* & localRoot){
    assert(localroot!=nullptr);// if localroot==nullptr here, root of subtree is null, so cannot be rotated.
    Node* aPtr = localRoot;
    assert(aPtr->rightChild!=nullptr);// if aPtr->rightChild==nullptr here, there is no right subtree, so no change caused by left rotation.
    localRoot = aPtr->rightChild;
    aPtr->rightChild = localRoot->leftChild;
    localRoot->leftChild = aPtr;
}

void BinarySearchTree<Key,Item>::rotateWholeTreeLeft(){
    rotateLeft(root);
}

