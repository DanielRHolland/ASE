#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

int main() {
	BinarySearchTree bst;
	
   bst.insert(22," Jane");
   bst.insert(22 ,"Mary");
   bst.insert(0 ,"Harold");
   bst.insert(9 ,"Edward");
   bst.insert(37 ,"Victoria");
   bst.insert(4 ,"Matilda");
   bst.insert(26 ,"Oliver");
   bst.insert(42 ,"Elizabeth");
   bst.insert(19 ,"Henry");
   bst.insert(4 ,"Stephen");
   bst.insert(24 ,"James");
   bst.insert(-1 ,"Edward");
   bst.insert(31 ,"Anne");
   bst.insert(23 ,"Elizabeth");
   bst.insert(1 ,"William");
   bst.insert(26 ,"Charles");
    
    

    cout << bst << endl;

    bst.displayEntries();
    bst.setTreeBalance();
    bst.displayTree();
    bst.rotateWholeTreeLeft();
    bst.displayTree();
    // bst.rotateWholeTreeRight();
    // bst.displayTree();
    cout << bst.rebalanceRoot() << endl;
    bst.displayTree();
    
	return 0;
}
