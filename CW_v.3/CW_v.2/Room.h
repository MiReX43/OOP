#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <sstream> // Для fromString
#include "RoomCategory.h" // Для displayDetails
using namespace std;
class Room {
    int roomNumber;
    int categoryId;
    int capacity;
    bool isAvailable;
    double pricePerNight;

public:
    static int roomCounter; // Статический счетчик

    Room(int number, int catId, int cap, bool avail, double price);

    int getRoomNumber() const;
    int getCategoryId() const;
    int getCapacity() const; // Добавим getter
    bool getAvailability() const;
    void updateStatus(bool status);
    double getPrice() const;

    void displayDetails(const RoomCategory& category) const; // Передаем по ссылке

    string toString() const;
    static Room fromString(const string& line);
};

#endif // ROOM_H