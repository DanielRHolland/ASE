#define BOOST_TEST_MODULE AseLab2
#include <boost/test/included/unit_test.hpp>
#include "BinarySearchTree.h"

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

BOOST_AUTO_TEST_CASE( test_remove_root_lone) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.remove(23);
    std::stringstream ss;
    ss << bst;
    bst.displayTree();
    BOOST_CHECK_EQUAL(ss.str(),"");
}

BOOST_AUTO_TEST_CASE( test_remove_child_singlechild ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.remove(12);
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"23: item A, ");
}

BOOST_AUTO_TEST_CASE( test_remove_root_singlechild ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.remove(23);
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"12: item -A, ");
}

BOOST_AUTO_TEST_CASE( test_remove_child_singlegrandchild ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.insert(2,"item -B");
    bst.remove(12);
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"2: item -B, 23: item A, ");
}

BOOST_AUTO_TEST_CASE( test_remove_root_twochildren ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.insert(56,"item B");
    bst.remove(23);
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"12: item -A, 56: item B, ");
}

BOOST_AUTO_TEST_CASE( test_tree_rotate_right_twochildren_maintains_structure ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.insert(56,"item B");
    bst.rotateWholeTreeRight();
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"12: item -A, 23: item A, 56: item B, ");
}

BOOST_AUTO_TEST_CASE( test_tree_rotate_left_twochildren_maintains_structure ) {
    BinarySearchTree bst;
    bst.insert(23,"item A");
    bst.insert(12,"item -A");
    bst.insert(56,"item B");
    bst.rotateWholeTreeLeft();
    std::stringstream ss;
    ss << bst;
    BOOST_CHECK_EQUAL(ss.str(),"12: item -A, 23: item A, 56: item B, ");
}