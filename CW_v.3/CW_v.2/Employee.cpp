#include "Employee.h"
#include <iostream> // Для cout

int Employee::employeeCounter = 1; // Инициализация статического счетчика

Employee::Employee(int id, std::string name, std::string phone, std::string email, std::string pos)
    : Person(id, std::move(name), std::move(phone), std::move(email)), position(std::move(pos)) {
    if (id >= employeeCounter) employeeCounter = id + 1;
}

void Employee::displayInfo() const {
    std::cout << "ID: " << getId()
        << ", Имя: " << getName()
        << ", Телефон: " << getPhone()
        << ", Email: " << getEmail()
        << ", Должность: " << position << std::endl;
}

std::string Employee::getPosition() const {
    return position;
}

std::string Employee::toString() const {
    return std::to_string(getId()) + "," + getName() + "," + getPhone() + "," + getEmail() + "," + position;
}

Employee Employee::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string idStr, name, phone, email, pos;
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, email, ',');
    std::getline(ss, pos, ',');
    int id = 0;
    if (!idStr.empty()) id = std::stoi(idStr);
    return Employee(id, name, phone, email, pos);
}