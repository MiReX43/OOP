#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Quadrilateral.h"

class Parallelogram : public Quadrilateral {
protected:
    double height; // ������ ���������������

public:
    Parallelogram(double a, double b, double h);
    double area() const override;

    // ���������� ��������� �������� (���������� �������)
    double operator+(const Parallelogram& other) const;
};

#endif // PARALLELOGRAM_H
