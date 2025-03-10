#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Quadrilateral.h"

class Trapezoid : public Quadrilateral {
protected:
    double height; // Высота трапеции

public:
    Trapezoid(double a, double b, double c, double d, double h);
    double area() const override;
};

#endif // TRAPEZOID_H
