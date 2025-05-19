#ifndef GUEST_H
#define GUEST_H
using namespace std;
#include "Person.h"
#include <string>
#include <sstream> // ��� fromString

class Guest : public Person {
    string passportData;

public:
    static int guestCounter; // ����������� ������� ��� ID

    Guest(int i, string name, string phone, string email, string passportData);

    void updateContactInfo(string newPhone, string newEmail);
    void displayInfo() const override;

    string getPassportData() const; // ������� getter ��� �������
    string toString() const;
    static Guest fromString(const string& line);
};

#endif // GUEST_H