#define BOOST_TEST_MODULE AseLab2
#include<boost/test/included/unit_test.hpp>
#include "BinarySearchTree.cpp"

BOOST_AUTO_TEST_CASE( my_addition_test ) {
    BOOST_CHECK_EQUAL( (1+2) , 3 );
}

BOOST_AUTO_TEST_CASE( test_insert_and_lookup_root_node  ) {
    BinarySearchTree bst;
    bst.insert(100,"root item");
    BOOST_CHECK_EQUAL(*bst.lookup(100),"root item");
}

BOOST_AUTO_TEST_CASE( test_5_inserts_and_lookup  ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.insert(56,"item B");
    bst.insert(2,"item -B");
    bst.insert(232,"item C");
    BOOST_CHECK_EQUAL( *bst.lookup(23) , "item A" );
}

BOOST_AUTO_TEST_CASE( test_remove_root) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.remove(23);
    stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"");
}
