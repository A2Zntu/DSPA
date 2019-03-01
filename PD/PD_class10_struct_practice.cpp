#include <iostream>
using namespace std;

// we difine "Point" as two-dimention int
struct Point{
	int x; 
	int y; 
};
typedef Point Vector; 


Point vector(Point A, Point B){
	//Point as parameter 
	Point vecXY; 
	vecXY.x = B.x - A.x;
	vecXY.y = B.y - A.y;
	return vecXY; 
	
}
 


int main(){
	Point a = {0, 0}, b = {10, 20}; 
	Vector vecAB = vector(a, b); 
	cout << vecAB.x << " " << vecAB.y << endl; 
	return 0; 
	
}
