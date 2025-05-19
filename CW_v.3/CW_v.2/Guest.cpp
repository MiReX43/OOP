#include "Guest.h"
#include <iostream> // ��� cout � displayInfo
using namespace std;
int Guest::guestCounter = 1; // ������������� ������������ ��������

Guest::Guest(int i, string name, string phone, string email, string passportData)
    : Person(i, move(name), move(phone), move(email)), passportData(move(passportData)) {
    if (i >= guestCounter) guestCounter = i + 1;
}

void Guest::updateContactInfo(string newPhone, string newEmail) {
    setPhone(newPhone); // ���������� ������� �������� ������
    setEmail(newEmail);
}

void Guest::displayInfo() const {
    cout << "ID: " << getId()
        << ", ���: " << getName()
        << ", �������: " << getPhone()
        << ", Email: " << getEmail()
        << endl; // ���������� ������ ����� �� �������, �� ����� ��������
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
    getline(ss, passport, ','); // passportData ����� ���� ��������� � �� ����� ������� ����� ����, ���� ��� ���� �������
    int id = 0;
    if (!idStr.empty()) id = stoi(idStr);
    return Guest(id, name, phone, email, passport);
}