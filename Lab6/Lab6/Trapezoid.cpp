#include "Trapezoid.h"

Trapezoid::Trapezoid(double a, double b, double c, double d, double h)
    : Quadrilateral(a, b, c, d), height(h) {}

double Trapezoid::area() const {
    return 0.5 * (a + b) * height;
}
