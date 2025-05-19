#include "Person.h"

Person::Person(int id, std::string name, std::string phone, std::string email)
    : id(id), name(std::move(name)), phone(std::move(phone)), email(std::move(email)) {
}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }
std::string Person::getPhone() const { return phone; }
std::string Person::getEmail() const { return email; }

void Person::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

void Person::setEmail(const std::string& newEmail) {
    email = newEmail;
}