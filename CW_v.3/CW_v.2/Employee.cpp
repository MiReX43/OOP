#include "Employee.h"
#include <iostream> // Для cout
using namespace std;
int Employee::employeeCounter = 1; // Инициализация статического счетчика

Employee::Employee(int id, string name, string phone, string email, string pos)
    : Person(id, move(name), move(phone), move(email)), position(move(pos)) {
    if (id >= employeeCounter) employeeCounter = id + 1;
}

void Employee::displayInfo() const {
    cout << "ID: " << getId()
        << ", Имя: " << getName()
        << ", Телефон: " << getPhone()
        << ", Email: " << getEmail()
        << ", Должность: " << position << endl;
}

string Employee::getPosition() const {
    return position;
}

string Employee::toString() const {
    return to_string(getId()) + "," + getName() + "," + getPhone() + "," + getEmail() + "," + position;
}

Employee Employee::fromString(const string& line) {
    stringstream ss(line);
    string idStr, name, phone, email, pos;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, pos, ',');
    int id = 0;
    if (!idStr.empty()) id = stoi(idStr);
    return Employee(id, name, phone, email, pos);
}