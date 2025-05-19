#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sstream> // ��� fromString

#include "Guest.h" // ���������� ������ ����������� ��� ������������ � display
#include "Room.h"  // ����������

class Booking {
    int bookingID;
    int guestId;
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    std::string status; // ��������: "�������", "��������", "���������"

public:
    static int bookingCounter; // ����������� �������

    // ����������� ��� �������� �� �����
    Booking(int id, int gid, int rn, std::string in, std::string out, std::string st);
    // ����������� ��� ������ ������������
    Booking(const Guest& g, const Room& r, std::string in, std::string out);

    int getID() const;
    int getGuestId() const;
    int getRoomNumber() const;
    std::string getCheckInDate() const;  // ������� getter
    std::string getCheckOutDate() const; // ������� getter
    std::string getStatus() const;

    void confirmBooking();
    void cancelBooking();
    void completeBooking(); // ������������� �� completBooking

    double calculateCost(double pricePerNight) const; // ���� �������� � ������������� ����������� ����
    void display(const Guest& guest, const Room& room) const; // �������� �� ������

    std::string toString() const;
    static Booking fromString(const std::string& line);
};

#endif // BOOKING_H