#ifndef GUEST_H
#define GUEST_H

#include "Person.h"
#include <string>
#include <sstream> // ��� fromString

class Guest : public Person {
    std::string passportData;

public:
    static int guestCounter; // ����������� ������� ��� ID

    Guest(int i, std::string name, std::string phone, std::string email, std::string passportData);

    void updateContactInfo(std::string newPhone, std::string newEmail);
    void displayInfo() const override;

    std::string getPassportData() const; // ������� getter ��� �������
    std::string toString() const;
    static Guest fromString(const std::string& line);
};

#endif // GUEST_H