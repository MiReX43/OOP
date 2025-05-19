#include "Booking.h"
#include <iostream> // ��� cout

using namespace std;
int Booking::bookingCounter = 1; // �������������

// ����������� ��� �������� �� �����
Booking::Booking(int id, int gid, int rn, string in, string out, string st)
    : bookingID(id), guestId(gid), roomNumber(rn),
    checkInDate(move(in)), checkOutDate(move(out)), status(move(st)) {
    if (id >= bookingCounter) bookingCounter = id + 1;
}

// ����������� ��� ������ ������������
Booking::Booking(const Guest& g, const Room& r, string in, string out)
    : bookingID(bookingCounter++), guestId(g.getId()), roomNumber(r.getRoomNumber()),
    checkInDate(move(in)), checkOutDate(move(out)), status("�������") {
}

int Booking::getID() const { return bookingID; }
int Booking::getGuestId() const { return guestId; }
int Booking::getRoomNumber() const { return roomNumber; }
string Booking::getCheckInDate() const { return checkInDate; }
string Booking::getCheckOutDate() const { return checkOutDate; }
string Booking::getStatus() const { return status; }

void Booking::confirmBooking() { status = "�������"; }
void Booking::cancelBooking() { status = "��������"; }
void Booking::completeBooking() { status = "���������"; }

// TODO: ����������� ���������� ������ ��������� �� ������ ���
double Booking::calculateCost(double pricePerNight) const {
    // ���� ��� ��������, ����� ����� ����������� ������ ���������� �����
    // ��������, ����� ������������ tm � mktime ��� ������� ���
    return 3.0 * pricePerNight; // ������������� ���������� ����� ��� �������
}

void Booking::display(const Guest& guest, const Room& room) const {
    cout << "ID ������������: " << bookingID
        << ", �����: " << guest.getName()
        << ", ����� #: " << room.getRoomNumber()
        << ", ��: " << checkInDate
        << " ��: " << checkOutDate
        << ", ������: " << status
        << endl;
}

string Booking::toString() const {
    return to_string(bookingID) + "," + to_string(guestId) + "," + to_string(roomNumber) + "," +
        checkInDate + "," + checkOutDate + "," + status;
}

Booking Booking::fromString(const string& line) {
    stringstream ss(line);
    string bidStr, gidStr, rnStr, inDate, outDate, st;
    getline(ss, bidStr, ',');
    getline(ss, gidStr, ',');
    getline(ss, rnStr, ',');
    getline(ss, inDate, ',');
    getline(ss, outDate, ',');
    getline(ss, st); // ������ �� ����� ������

    int bid = 0;
    if (!bidStr.empty()) bid = stoi(bidStr);
    int gid = 0;
    if (!gidStr.empty()) gid = stoi(gidStr);
    int rn = 0;
    if (!rnStr.empty()) rn = stoi(rnStr);

    return Booking(bid, gid, rn, inDate, outDate, st);
}