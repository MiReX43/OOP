#include "Person.h"
using namespace std;
Person::Person(int id, string name, string phone, string email)
    : id(id), name(move(name)), phone(move(phone)), email(move(email)) {
}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }
string Person::getEmail() const { return email; }

void Person::setPhone(const string& newPhone) {
    phone = newPhone;
}

void Person::setEmail(const string& newEmail) {
    email = newEmail;
}