#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>
#include <sstream> // ��� fromString

class Employee : public Person {
    std::string position;

public:
    static int employeeCounter; // ����������� �������

    Employee(int id, std::string name, std::string phone, std::string email, std::string pos);

    void displayInfo() const override;
    std::string getPosition() const; // ������� getter

    std::string toString() const;
    static Employee fromString(const std::string& line);
};

#endif // EMPLOYEE_H