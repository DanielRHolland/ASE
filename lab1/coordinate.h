#include <iostream>
using namespace std;

class Coordinate	{
	public:
	int xco;
	int yco;
	Coordinate(int,int);
	void display();
	static void test();
//	Coordinate operator+(Coordinate);
};

Coordinate operator+(Coordinate,Coordinate);

