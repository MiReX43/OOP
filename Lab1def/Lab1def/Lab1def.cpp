#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double computeA(double a, double b) {
	return (a + sin(a)) / (b);
}

double computeB(double a, double b) {
	return (a + sin(a)) / (sin(b) + b);
}

double computeC(double a, double b) {
	return (a + sin(b)) / (sin(a) + b);
}

double computeD(double a, double b, double c) {
	return (a + sin(b)) / (sin(c) + b);
}

int main() {

	//double y1, y2, y3, y4;

	double y1 = computeA(1, 3) + computeA(5, 3) + computeA(3, 3);
	double y2 = computeB(2, 5) + computeB(6, 3) + computeB(1, 4);
	double y3 = computeC(1, 4) + computeC(7, 5) + computeC(3, 2);
	double y4 = computeC(2, 3) + computeC(1, 5) + computeD(4, 7, 3);

	/*y1 = ((1 +sin(1))/3) + ((5 + sin(5)) / 3) + ((3 + sin(3)) / 3);

	y2 = ((2 + sin(2)) / (sin(5) + 5)) + ((6 + sin(6)) / (sin(3) + 3)) + ((1 + sin(1)) / (sin(4) + 4));

	y3 = ((1 + sin(4)) / (sin(1) + 4)) + ((7 + sin(5)) / (sin(7) + 5)) + ((3 + sin(2)) / (sin(3) + 2));
	
	y4 = ((2 + sin(3)) / (sin(2) + 3)) + ((1 + sin(5)) / (sin(1) + 5)) + ((4 + sin(7)) / (sin(3) + 7));*/

	cout << "y1 = " << y1 << endl;
	cout << "y2 = " << y2 << endl;
	cout << "y3 = " << y3 << endl;
	cout << "y4 = " << y4 << endl;
}