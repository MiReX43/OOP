#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Quadrilateral.h"

class Parallelogram : public Quadrilateral {
protected:
    double height; // Высота параллелограмма

public:
    Parallelogram(double a, double b, double h);
    double area() const override;

    // Перегрузка оператора сложения (складывает площади)
    double operator+(const Parallelogram& other) const;
};

#endif // PARALLELOGRAM_H
