#include "BinarySearchTree.h"

struct BinarySearchTree::Node {
    Key key;
    Item item;
    Node* leftChild;
    Node* rightChild;
    int balance;
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
    this->balance = 0;
}


void BinarySearchTree::insert(Key key, Item item) {
    if (root == nullptr) {
        root = new Node(key, item);
        } else {
        insertRecursive(key, item, root);
    }
};

//returns true if height of sub-tree increased
bool BinarySearchTree::insertRecursive(Key key, Item item, Node* nodePtr) {
    if (nodePtr->key == key) {
        nodePtr->item = item;
    } else {
        bool isChildOnLeft = nodePtr->key > key;
        Node* & child = isChildOnLeft ? nodePtr->leftChild : nodePtr->rightChild;
        if (child!=nullptr) {
            //TODO - find why 9:Edward bal fac is -2, should be -1
            if (insertRecursive(key, item, child) ) {
                nodePtr->balance += isChildOnLeft ? -1 : 1;
                assert(nodePtr->balance>=-2 && nodePtr->balance<=2);
                return nodePtr->balance == 2 || nodePtr->balance == -2;
            } else return false;
        }   else  {
            child = new Node(key, item);
            nodePtr->balance += isChildOnLeft ? -1 : 1;
            return nodePtr->leftChild!=nullptr ^ nodePtr->rightChild!=nullptr;
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
        std::cout << n->key << ": " << n->item << "\t" << n->balance << std::endl;
    }
                 );
}

void BinarySearchTree::displayTree()
{
    this->preOrder([](Node* n,int gen) -> void {
        std::string out = std::to_string(gen)+"| ";
        for(int i=0; i<gen;i++) out += "      ";
        if (n== nullptr) std::cout << out + "*" << std::endl;
        else std::cout << out + std::to_string(n->key) + ": " + n->item << "\t" << n->balance << std::endl;
    }
    );
    
}

void BinarySearchTree::remove(BinarySearchTree::Key key)
{
    if (root!=nullptr) removeRecursive(key,root);
}

void BinarySearchTree::removeRecursive(Key key, Node* &nodePtr) {
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

BinarySearchTree::Node* BinarySearchTree::detachMinimumNode(Node* & nodePtr) {
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

void BinarySearchTree::rotateRight(Node* & localRoot){
    assert(localRoot!=nullptr);// if localroot==nullptr here, root of subtree is null, so cannot be rotated.
    Node* bPtr = localRoot;
    int b_before = bPtr->balance;
    assert(bPtr->leftChild!=nullptr);// if lbPtr->leftChild==nullptr here, there is no left subtree, so no change caused by right rotation.
    localRoot = bPtr->leftChild;
    int a_before = localRoot->balance;
    bPtr->leftChild = localRoot->rightChild;
    localRoot->rightChild = bPtr;
    bPtr->balance = b_before + 1 + std::max(-a_before,0);
    localRoot->balance = a_before + 1 + std::max(bPtr->balance,0);
}

void BinarySearchTree::rotateWholeTreeRight(){
    rotateRight(root);
}

void BinarySearchTree::rotateLeft(Node* & localRoot){

    assert(localRoot!=nullptr);// if localroot==nullptr here, root of subtree is null, so cannot be rotated.
    Node* aPtr = localRoot;
    assert(aPtr->rightChild!=nullptr);// if aPtr->rightChild==nullptr here, there is no right subtree, so no change caused by left rotation.
    localRoot = aPtr->rightChild;
    aPtr->rightChild = localRoot->leftChild;
    localRoot->leftChild = aPtr;
}

void BinarySearchTree::rotateWholeTreeLeft(){
    rotateLeft(root);
}

int BinarySearchTree::setBalanceRecursive(Node* nodePtr) {
    int leftChildHeight = nodePtr->leftChild != nullptr ?
        setBalanceRecursive(nodePtr->leftChild) : 0;
    int rightChildHeight = nodePtr->rightChild != nullptr ?
        setBalanceRecursive(nodePtr->rightChild) : 0;
    nodePtr->balance = rightChildHeight - leftChildHeight;
    return 1 + (rightChildHeight>leftChildHeight? rightChildHeight :leftChildHeight);
}

void BinarySearchTree::setTreeBalance() {
    setBalanceRecursive(root);
}

bool BinarySearchTree::rebalanceRoot() {
    return rebalance(root);
}


//return true if height changed
bool BinarySearchTree::rebalance(Node* & localRoot) {
    int bal = localRoot->balance;
    //Assuming -2<=balance<=2
    assert(bal>=-2 && bal<=2);
    if (bal==2) {
        //balance +ve, so should have a rightchild
        assert(localRoot->rightChild!=nullptr);
        Node* & rchild = localRoot->rightChild;
        if (rchild->balance==1){
            rotateLeft(localRoot);
            return true;
        } else if (rchild->balance==0) {
            rotateLeft(localRoot);
            return false;
        } else if (rchild->balance==-1){
            rotateRight(rchild);
            rotateLeft(localRoot);
            return true;
        }
    } else if(bal==-2) {
        //balance -ve, so should have a leftchild
        assert(localRoot->leftChild!=nullptr);
        Node* & lchild = localRoot->leftChild;
        if (lchild->balance==-1) {
            rotateRight(localRoot);
            return true;
        } else if (lchild->balance==0) {
            rotateRight(localRoot);
            return false;
        } else if (lchild->balance==1) {    
            rotateLeft(lchild);
            rotateRight(localRoot);
            return true;
        }
    }
    return false;
}