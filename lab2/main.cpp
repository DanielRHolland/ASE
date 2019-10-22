#include "BinarySearchTree.h"
#include <iostream>
using namespace std;
void print(string s) {
    cout << s <<", ";
}

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
    
    cout << "PreOrderTree:\t";
  //  bst.preOrder(printTreeLine);
    cout<<endl;

    cout << "InOrder:\t";    
    bst.inOrder(print);
    cout<<endl;
    
    cout << "PostOrder:\t";
    bst.postOrder(print);
    cout<<endl;
    
    cout << bst << endl;
    
	return 0;
}
