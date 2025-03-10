#include "Quadrilateral.h"

using namespace std;

Quadrilateral::Quadrilateral(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d) {}

double Quadrilateral::perimeter() const {
    return a + b + c + d;
}

ostream& operator<<(ostream& os, const Quadrilateral& q) {
    os << "Стороны: " << q.a << ", " << q.b << ", " << q.c << ", " << q.d;
    return os;
}
