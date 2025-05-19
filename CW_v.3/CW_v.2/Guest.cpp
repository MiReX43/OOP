#include "Guest.h"
#include <iostream> // Для cout в displayInfo

int Guest::guestCounter = 1; // Инициализация статического счетчика

Guest::Guest(int i, std::string name, std::string phone, std::string email, std::string passportData)
    : Person(i, std::move(name), std::move(phone), std::move(email)), passportData(std::move(passportData)) {
    if (i >= guestCounter) guestCounter = i + 1;
}

void Guest::updateContactInfo(std::string newPhone, std::string newEmail) {
    setPhone(newPhone); // Используем сеттеры базового класса
    setEmail(newEmail);
}

void Guest::displayInfo() const {
    std::cout << "ID: " << getId()
        << ", ФИО: " << getName()
        << ", Телефон: " << getPhone()
        << ", Email: " << getEmail()
        << std::endl; // Паспортные данные здесь не выводим, но можно добавить
}

std::string Guest::getPassportData() const {
    return passportData;
}

std::string Guest::toString() const {
    return std::to_string(getId()) + "," + getName() + "," + getPhone() + "," + getEmail() + "," + passportData;
}

Guest Guest::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string idStr, name, phone, email, passport;
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, email, ',');
    std::getline(ss, passport, ','); // passportData может быть последним и не иметь запятой после себя, если так файл устроен
    int id = 0;
    if (!idStr.empty()) id = std::stoi(idStr);
    return Guest(id, name, phone, email, passport);
}