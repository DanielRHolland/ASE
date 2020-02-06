#define BOOST_TEST_MODULE AseHashtable
#include <boost/test/included/unit_test.hpp>
#include "HashTable.h"

BOOST_AUTO_TEST_CASE( my_addition_test ) {
    BOOST_CHECK_EQUAL( (1+2) , 3 );
}

BOOST_AUTO_TEST_CASE( insert_lookup_one_item_kvbothstrings ) {
    std::string key = "first_key";
    std::string item = "first_item";
    HashTable<std::string,std::string> hstbl;
    hstbl.insert(key, item);
    BOOST_CHECK_EQUAL( *hstbl.lookup(key) , item );
}

BOOST_AUTO_TEST_CASE( insert_lookup_one_item_kvbothints ) {
    int key = 34;
    int item = 25;
    HashTable<int,int> hstbl;
    hstbl.insert(key, item);
    BOOST_CHECK_EQUAL( *hstbl.lookup(key) , item );
}

BOOST_AUTO_TEST_CASE( insert_lookup_one_item_kintvstring ) {
    int key = 34;
    std::string item = "first_item";
    HashTable<int,std::string> hstbl;
    hstbl.insert(key, item);
    BOOST_CHECK_EQUAL( *hstbl.lookup(key) , item );
}


BOOST_AUTO_TEST_CASE( insert_lookup_fifty_items_kvbothstrings ) {
    HashTable<std::string,std::string> hstbl;
    for (int i = 0; i < 50; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert("key"+num, "item"+num);
    }
    BOOST_CHECK_EQUAL( *hstbl.lookup("key25") , "item25" );
}

BOOST_AUTO_TEST_CASE( insert_lookup_onethousand_items_kvbothstrings ) {
    HashTable<std::string,std::string> hstbl;
    for (int i = 0; i < 1000; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert("key"+num, "item"+num);
    }
    BOOST_CHECK_EQUAL( *hstbl.lookup("key545") , "item545" );
}

BOOST_AUTO_TEST_CASE( insert_remove_lookup ) {
    HashTable<std::string,std::string> hstbl;
    for (int i = 0; i < 100; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert("key"+num, "item"+num);
    }
    hstbl.remove("key15");
    hstbl.remove("key55");
    BOOST_CHECK_EQUAL( *hstbl.lookup("key25") , "item25" );
    BOOST_CHECK_EQUAL( hstbl.lookup("key55") , nullptr );
    BOOST_CHECK_EQUAL( hstbl.lookup("key15") , nullptr );
}

BOOST_AUTO_TEST_CASE( loadfactor_one ) {
    HashTable<int,int> hstbl;
    for (int i = 0; i < 100; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert(i,i);
    }
    BOOST_CHECK_EQUAL( hstbl.loadFactor() , 1.0 );
}

BOOST_AUTO_TEST_CASE( loadfactor_half ) {
    HashTable<int,int> hstbl;
    for (int i = 0; i < 50; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert(i,i);
    }
    BOOST_CHECK_EQUAL( hstbl.loadFactor() , 0.5 );
}

BOOST_AUTO_TEST_CASE( loadfactor_double ) {
    HashTable<int,int> hstbl;
    for (int i = 0; i < 200; ++i) {
        std::string num = std::to_string(i);
        hstbl.insert(i,i);
    }
    BOOST_CHECK_EQUAL( hstbl.loadFactor() , 2.0 );
}

