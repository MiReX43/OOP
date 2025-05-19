#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;
// ---------------- ����������� ����� Person ----------------
class Person {
protected:
    int id;
    string name;
    string phone;
    string email;

public:
    Person(int id, string name, string phone, string email);
    virtual ~Person() = default; // ����� �������� ����������� ����������

    virtual void displayInfo() const = 0; // ����� ����������� �����

    int getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

protected: // ������� ������� �����������, ���� ��� ����� ������ �����������
    void setPhone(const string& newPhone);
    void setEmail(const string& newEmail);
};

#endif // PERSON_H