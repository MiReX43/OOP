#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <sstream> // ��� fromString
#include "RoomCategory.h" // ��� displayDetails

class Room {
    int roomNumber;
    int categoryId;
    int capacity;
    bool isAvailable;
    double pricePerNight;

public:
    static int roomCounter; // ����������� �������

    Room(int number, int catId, int cap, bool avail, double price);

    int getRoomNumber() const;
    int getCategoryId() const;
    int getCapacity() const; // ������� getter
    bool getAvailability() const;
    void updateStatus(bool status);
    double getPrice() const;

    void displayDetails(const RoomCategory& category) const; // �������� �� ������

    std::string toString() const;
    static Room fromString(const std::string& line);
};

#endif // ROOM_H