#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sstream> // ��� fromString
#include "Guest.h" // ���������� ������ ����������� ��� ������������ � display
#include "Room.h"  // ����������
using namespace std;
class Booking {
    int bookingID;
    int guestId;
    int roomNumber;
    string checkInDate;
    string checkOutDate;
    string status; // ��������: "�������", "��������", "���������"

public:
    static int bookingCounter; // ����������� �������

    // ����������� ��� �������� �� �����
    Booking(int id, int gid, int rn, string in, string out, string st);
    // ����������� ��� ������ ������������
    Booking(const Guest& g, const Room& r, string in, string out);

    int getID() const;
    int getGuestId() const;
    int getRoomNumber() const;
    string getCheckInDate() const;  // ������� getter
    string getCheckOutDate() const; // ������� getter
    string getStatus() const;

    void confirmBooking();
    void cancelBooking();
    void completeBooking(); // ������������� �� completBooking

    double calculateCost(double pricePerNight) const; // ���� �������� � ������������� ����������� ����
    void display(const Guest& guest, const Room& room) const; // �������� �� ������

    string toString() const;
    static Booking fromString(const string& line);
};

#endif // BOOKING_H