#ifndef EMPLOYEE_H
#define EMPLOYEE_H
using namespace std;
#include "Person.h"
#include <string>
#include <sstream> // Для fromString

class Employee : public Person {
    string position;

public:
    static int employeeCounter; // Статический счетчик

    Employee(int id, string name, string phone, string email, string pos);

    void displayInfo() const override;
    string getPosition() const; // Добавим getter

    string toString() const;
    static Employee fromString(const string& line);
};

#endif // EMPLOYEE_H