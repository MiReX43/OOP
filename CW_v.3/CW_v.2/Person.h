#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

// ---------------- Абстрактный класс Person ----------------
class Person {
protected:
    int id;
    std::string name;
    std::string phone;
    std::string email;

public:
    Person(int id, std::string name, std::string phone, std::string email);
    virtual ~Person() = default; // Важно добавить виртуальный деструктор

    virtual void displayInfo() const = 0; // Чисто виртуальный метод

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;

protected: // Сделаем сеттеры защищенными, если они нужны только наследникам
    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);
};

#endif // PERSON_H