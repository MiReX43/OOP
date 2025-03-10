#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include <iostream>
#include <cmath>

using namespace std;

class Quadrilateral {
protected:
    double a, b, c, d; // Стороны четырехугольника

public:
    Quadrilateral(double a, double b, double c, double d);
    virtual ~Quadrilateral() {}

    virtual double perimeter() const;
    virtual double area() const = 0; // Чисто виртуальная функция

    friend ostream& operator<<(ostream& os, const Quadrilateral& q);
};

#endif // QUADRILATERAL_H
