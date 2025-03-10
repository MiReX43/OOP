#include "Parallelogram.h"

Parallelogram::Parallelogram(double a, double b, double h)
    : Quadrilateral(a, b, a, b), height(h) {}

double Parallelogram::area() const {
    return a * height;
}

double Parallelogram::operator+(const Parallelogram& other) const {
    return this->area() + other.area();
}
