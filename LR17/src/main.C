#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

#include "vector/vector.h"


struct Point {
	int x, y, z;

	Point(int x_, int y_, int z_) : x{x_}, y{y_}, z{z_} {};
	Point(int val) : x{val}, y{val}, z{val} {};
	friend std::ostream& operator<< (std::ostream& os, const Point& pt);
};

std::ostream& operator<< (std::ostream& os, const Point& pt) {
	os << "{" << pt.x << ", " << pt.y << ", " << pt.z << '}';
	return os;
};


int main() {
	Vector<Point> test;
 	for(int i=0; i<10; i++)
 		test.PushBack(Point(i));
 	test.ListAll();

 	test.Erase(123);
 	test.ListAll();
};
