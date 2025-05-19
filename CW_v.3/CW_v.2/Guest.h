#ifndef GUEST_H
#define GUEST_H

#include "Person.h"
#include <string>
#include <sstream> // Для fromString

class Guest : public Person {
    std::string passportData;

public:
    static int guestCounter; // Статический счетчик для ID

    Guest(int i, std::string name, std::string phone, std::string email, std::string passportData);

    void updateContactInfo(std::string newPhone, std::string newEmail);
    void displayInfo() const override;

    std::string getPassportData() const; // Добавим getter для полноты
    std::string toString() const;
    static Guest fromString(const std::string& line);
};

#endif // GUEST_H