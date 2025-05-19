#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;
// ---------------- Абстрактный класс Person ----------------
class Person {
protected:
    int id;
    string name;
    string phone;
    string email;

public:
    Person(int id, string name, string phone, string email);
    virtual ~Person() = default; // Важно добавить виртуальный деструктор

    virtual void displayInfo() const = 0; // Чисто виртуальный метод

    int getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

protected: // Сделаем сеттеры защищенными, если они нужны только наследникам
    void setPhone(const string& newPhone);
    void setEmail(const string& newEmail);
};

#endif // PERSON_H