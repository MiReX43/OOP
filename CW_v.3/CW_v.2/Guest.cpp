#include "Guest.h"
#include <iostream> // Для cout в displayInfo
using namespace std;
int Guest::guestCounter = 1; // Инициализация статического счетчика

Guest::Guest(int i, string name, string phone, string email, string passportData)
    : Person(i, move(name), move(phone), move(email)), passportData(move(passportData)) {
    if (i >= guestCounter) guestCounter = i + 1;
}

void Guest::updateContactInfo(string newPhone, string newEmail) {
    setPhone(newPhone); // Используем сеттеры базового класса
    setEmail(newEmail);
}

void Guest::displayInfo() const {
    cout << "ID: " << getId()
        << ", ФИО: " << getName()
        << ", Телефон: " << getPhone()
        << ", Email: " << getEmail()
        << endl; // Паспортные данные здесь не выводим, но можно добавить
}

string Guest::getPassportData() const {
    return passportData;
}

string Guest::toString() const {
    return to_string(getId()) + "," + getName() + "," + getPhone() + "," + getEmail() + "," + passportData;
}

Guest Guest::fromString(const string& line) {
    stringstream ss(line);
    string idStr, name, phone, email, passport;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, passport, ','); // passportData может быть последним и не иметь запятой после себя, если так файл устроен
    int id = 0;
    if (!idStr.empty()) id = stoi(idStr);
    return Guest(id, name, phone, email, passport);
}