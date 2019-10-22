#include "coordinate.h"
#include <iostream>
#include <vector>
using namespace std;

//template<typename T> std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec)

template<typename T1,<template<typename>>> std::ostream & operator<<(std::ostream & os, const T1 & vec)
{
	long pos = os.tellp();
	if (pos > 0) {
		os.seekp(pos-1);
		os << ',';
	} else {
		os << '[';
	}
	
	for (auto iter = vec.cbegin(); iter+1 != vec.cend(); iter++) {
		os << *iter << ','; 
	}
	os << *(vec.cend()-1) <<']';

	return os;
}

int main() {
	//Coordinate::test();
	std::vector<int> v1 = {1,2,3};
	cout << v1.front() << endl;
	std::vector<int> v2 = {8,7,6};
	cout << v2.front() << endl;
	cout << "Vec test:~~~~~~~~~" << endl;
	cout <<	v1 << v2 <<endl;
	cout << v1.front() << endl;
	std::vector<string> vs1 = {"one","two","three"};
	cout << vs1 << endl;
	return 0;
}