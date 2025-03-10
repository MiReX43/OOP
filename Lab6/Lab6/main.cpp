#include "Parallelogram.h"
#include "Trapezoid.h"

using namespace std;

int main() {
    
    setlocale(LC_ALL,"RUS");

    Trapezoid trap(8, 5, 4, 3, 6);
    Parallelogram para1(7, 4, 5);
    Parallelogram para2(6, 3, 4);

    cout << "Òנאןוצטÿ:\n" << trap << "\nÏונטלוענ: "
        << trap.perimeter() << "\nÏכמשאהü: " << trap.area() << "\n\n";

    cout << "Ïאנאככוכמדנאלל 1:\n" << para1 << "\nÏונטלוענ: "
        << para1.perimeter() << "\nÏכמשאהü: " << para1.area() << "\n\n";

    cout << "Ïאנאככוכמדנאלל 2:\n" << para2 << "\nÏונטלוענ: "
        << para2.perimeter() << "\nÏכמשאהü: " << para2.area() << "\n\n";

    cout << "Ñףללא ןכמשאהוי הגףץ ןאנאככוכמדנאללמג: " << (para1 + para2) << "\n";

    return 0;
}
