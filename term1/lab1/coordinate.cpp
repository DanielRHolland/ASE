#include "coordinate.h"

Coordinate::Coordinate(int x,int y) {
	xco = x;
	yco = y;
}

void Coordinate::display() {
	std::cout <<'('<< xco <<','<< yco <<')'<< std::endl;
}

/*
Coordinate Coordinate::operator+(Coordinate c2) {
	int x = this->xco + c2.xco;
	int y = this->yco + c2.yco;
	return Coordinate(x,y);
}*/

Coordinate operator+(Coordinate c1, Coordinate c2) {
	int x = c1.xco + c2.xco;
	int y = c1.yco + c2.yco;
	return Coordinate(x,y);
}

void Coordinate::test() {
	cout << "Example Start"<< endl;
		Coordinate c1 = Coordinate(2,5); 
		c1.display();
		Coordinate c2 = Coordinate(4,7); 
		c2.display();
		Coordinate c3 = Coordinate(8,1); 
		c3.display();
		(c2 = c3,c1).display();
		cout << "=========="<< endl;
		c1.display(),c2.display(),c3.display();
		cout << "=========="<< endl;
		Coordinate c4 = Coordinate(2,5);
		c4.display();
		cout << "=========="<< endl;
		(c4+c3).display();
		cout << "Example End"<< endl;
}
