#include "BinarySearchTree.h"
#include "HashTable.h"
#include <iostream>

int main() {
    HashTable<std::string, std::string> htbl;
    std::cout<< htbl.hash("hello_key")<<std::endl;
    htbl.insert("hello_key", "hello_item");
    htbl.insert("hello_key", "hello_item_replaced");
    htbl.insert("another_key", "A different thing");

    std::cout << *htbl.lookup("hello_key") << std::endl;

    return 0;
}
//////////////////////////////////////////////////////////////////
//    BinarySearchTree bst;
//
//    bst.insert(22," Jane");
//    bst.insert(22 ,"Mary");
//    bst.insert(0 ,"Harold");
//    bst.insert(9 ,"Edward");
//    bst.insert(37 ,"Victoria");
//    bst.insert(4 ,"Matilda");
//    bst.insert(26 ,"Oliver");
//    bst.insert(42 ,"Elizabeth");
//    bst.insert(19 ,"Henry");
//    bst.insert(4 ,"Stephen");
//    bst.insert(24 ,"James");
//    bst.insert(-1 ,"Edward");
//    bst.insert(31 ,"Anne");
//    bst.insert(23 ,"Elizabeth");
//    bst.insert(1 ,"William");
//    bst.insert(26 ,"Charles");
//
    

//     std::cout << bst << std::endl;

//     bst.displayEntries();
//     bst.setTreeBalance();
//     bst.displayTree();
//     bst.rotateWholeTreeLeft();
//     bst.displayTree();
//     bst.rotateWholeTreeRight();
//     bst.displayTree();

//    std::cout << bst.rebalanceRoot() << std::endl;
//     bst.displayTree();
    

