#ifndef GUEST_H
#define GUEST_H
using namespace std;
#include "Person.h"
#include <string>
#include <sstream> // Для fromString

class Guest : public Person {
    string passportData;

public:
    static int guestCounter; // Статический счетчик для ID

    Guest(int i, string name, string phone, string email, string passportData);

    void updateContactInfo(string newPhone, string newEmail);
    void displayInfo() const override;

    string getPassportData() const; // Добавим getter для полноты
    string toString() const;
    static Guest fromString(const string& line);
};

#endif // GUEST_H