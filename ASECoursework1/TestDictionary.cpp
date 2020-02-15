#define BOOST_TEST_MODULE AseLab2
#include<boost/test/included/unit_test.hpp>
#include "dictionary.h"

using Containers::Dictionary;
using std::string;

BOOST_AUTO_TEST_CASE( test_insert_and_lookup  ) {
    Dictionary<int,string> dict;
    dict.insert(100,"root item");
    BOOST_CHECK_NE(dict.lookup(100), nullptr);
    BOOST_CHECK_EQUAL(*dict.lookup(100),"root item");
}

BOOST_AUTO_TEST_CASE( test_5_inserts_and_lookup  ) {
    Dictionary<int, string> dict;
    dict.insert(23, "item A");
    dict.insert(12, "item -A");
    dict.insert(56, "item B");
    dict.insert(2, "item -B");
    dict.insert(232, "item C");
    BOOST_CHECK_NE(dict.lookup(23), nullptr);
    BOOST_CHECK_EQUAL(*dict.lookup(23) , "item A" );
}


//1. Each possible value of type ‘Key’ is considered to be in either a present or absent state.
//2. If a key is in a present state, then it has an associated item of type ‘Item’.
//3. The default constructor produces a dictionary in which all keys are considered to be absent.
//4. After a call of ‘insert(k,i)’, the key ‘k’ is considered to be present, and the associated item
//becomes ‘i’.

BOOST_AUTO_TEST_CASE( insert_makes_item_present ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    BOOST_CHECK_EQUAL(dict.lookup(1), nullptr); //Check key is not present
    string v = "value";
    dict.insert(1, v);
    BOOST_CHECK_EQUAL(*dict.lookup(1), v); //Check key is present with item v
}

BOOST_AUTO_TEST_CASE( insert_overwrites ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    BOOST_CHECK_EQUAL(dict.lookup(1), nullptr); //Check key is not present
    string v = "value";
    dict.insert(1, v);
    BOOST_CHECK_EQUAL(*dict.lookup(1), v); //Check key is present with item v
    string replacement = "new value";
    dict.insert(1, replacement);
    BOOST_CHECK_EQUAL(*dict.lookup(1), replacement); //Check key is present with item replacement
}


//5. After a call of ‘remove(k)’, the key ‘k’ is considered to be absent.

BOOST_AUTO_TEST_CASE( remove_removes ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    BOOST_CHECK_EQUAL(dict.lookup(1), nullptr); //Check key is not present
    string v = "value";
    dict.insert(1, v);
    BOOST_CHECK_EQUAL(*dict.lookup(1), v); //Check key is present with item v
    dict.remove(1);
    BOOST_CHECK_EQUAL(dict.lookup(1), nullptr); //Check key is absent
}


//6. A call of ‘lookup(k)’ should return a pointer to the associated item if the key ‘k’ is present;
//otherwise it should return ‘ nullptr ’.

BOOST_AUTO_TEST_CASE( constructor_creates_empty_dictionary) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    BOOST_CHECK_EQUAL( dict.lookup(1) , nullptr);
}

//7. A call of ‘insert(k,i)’ should return ‘true’ if the key ‘k’ was absent before the call; otherwise
//it should return ‘ false ’.

BOOST_AUTO_TEST_CASE( insert_true_if_k_already_exists ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    string v = "value";
    dict.insert(1, v);
    string replacement = "new value";
    BOOST_CHECK_EQUAL(dict.insert(1, replacement), true);
}


BOOST_AUTO_TEST_CASE( insert_false_if_k_not_already_existing ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    string v = "value";
    BOOST_CHECK_EQUAL(dict.insert(1, v), false);
}


//8. A call of ‘remove(k)’ should return ‘true’ if the key ‘k’ was present before the call; otherwise
//it should return ‘ false ’.

BOOST_AUTO_TEST_CASE( remove_true_if_k_existed ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    string v = "value";
    dict.insert(1, v);
    string replacement = "new value";
    BOOST_CHECK_EQUAL(dict.remove(1), true);
}


BOOST_AUTO_TEST_CASE( remove_false_if_k_did_not_exist ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    BOOST_CHECK_EQUAL(dict.remove(1), false);
}


//9. None of these member functions perform console I/O.


//Furthermore, to achieve a high grade for this task, your dictionary implementation should also:
//• not introduce any memory leaks;
//• provide a copy constructor and copy assignment operator that make a deep copy;
//• provide an efficient move constructor and move assignment operator ;
//• use template parameters to be parametrically polymorphic in the type of its keys and items;
//• provide a higher-order member function ‘removeIf()’, such that after a call of ‘removeIf(p)’,
//every key ‘k’ for which ‘p(k)’ returns ‘true’ is considered to be absent.

BOOST_AUTO_TEST_CASE( removeIf_removes_if_predicate ) {
    Dictionary<int, string> dict = Dictionary<int,string>();
    dict.insert(1, "something");
    dict.insert(2,"whatever");
    dict.insert(4, "qwerty");
    dict.insert(213, "uiop[]");
    dict.removeIf( [](int x)->bool {return x%2==0;}); //predicate checks if divisible by 2
    BOOST_CHECK_NE(dict.lookup(1), nullptr);
    BOOST_CHECK_EQUAL(dict.lookup(2), nullptr);
    BOOST_CHECK_EQUAL(dict.lookup(4), nullptr);
    BOOST_CHECK_NE(dict.lookup(213), nullptr);
}


//BOOST_AUTO_TEST_CASE( test_remove_root) {
//    Dictionary<int, string> bst;
//    bst.insert(23,"item A");
//    bst.remove(23);
//    stringstream ss;
//    ss << bst;
//    BOOST_CHECK_EQUAL(ss.str(),"");
//}