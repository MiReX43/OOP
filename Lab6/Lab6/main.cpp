#include "Parallelogram.h"
#include "Trapezoid.h"

using namespace std;

int main() {
    
    setlocale(LC_ALL,"RUS");

    Trapezoid trap(8, 5, 4, 3, 6);
    Parallelogram para1(7, 4, 5);
    Parallelogram para2(6, 3, 4);

    cout << "��������:\n" << trap << "\n��������: "
        << trap.perimeter() << "\n�������: " << trap.area() << "\n\n";

    cout << "�������������� 1:\n" << para1 << "\n��������: "
        << para1.perimeter() << "\n�������: " << para1.area() << "\n\n";

    cout << "�������������� 2:\n" << para2 << "\n��������: "
        << para2.perimeter() << "\n�������: " << para2.area() << "\n\n";

    cout << "����� �������� ���� ����������������: " << (para1 + para2) << "\n";

    return 0;
}
