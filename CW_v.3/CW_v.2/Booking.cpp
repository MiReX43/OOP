#include "Booking.h"
#include <iostream> // ��� cout


int Booking::bookingCounter = 1; // �������������

// ����������� ��� �������� �� �����
Booking::Booking(int id, int gid, int rn, std::string in, std::string out, std::string st)
    : bookingID(id), guestId(gid), roomNumber(rn),
    checkInDate(std::move(in)), checkOutDate(std::move(out)), status(std::move(st)) {
    if (id >= bookingCounter) bookingCounter = id + 1;
}

// ����������� ��� ������ ������������
Booking::Booking(const Guest& g, const Room& r, std::string in, std::string out)
    : bookingID(bookingCounter++), guestId(g.getId()), roomNumber(r.getRoomNumber()),
    checkInDate(std::move(in)), checkOutDate(std::move(out)), status("�������") {
}

int Booking::getID() const { return bookingID; }
int Booking::getGuestId() const { return guestId; }
int Booking::getRoomNumber() const { return roomNumber; }
std::string Booking::getCheckInDate() const { return checkInDate; }
std::string Booking::getCheckOutDate() const { return checkOutDate; }
std::string Booking::getStatus() const { return status; }

void Booking::confirmBooking() { status = "�������"; }
void Booking::cancelBooking() { status = "��������"; }
void Booking::completeBooking() { status = "���������"; }

// TODO: ����������� ���������� ������ ��������� �� ������ ���
double Booking::calculateCost(double pricePerNight) const {
    // ���� ��� ��������, ����� ����� ����������� ������ ���������� �����
    // ��������, ����� ������������ std::tm � mktime ��� ������� ���
    return 3.0 * pricePerNight; // ������������� ���������� ����� ��� �������
}

void Booking::display(const Guest& guest, const Room& room) const {
    std::cout << "ID ������������: " << bookingID
        << ", �����: " << guest.getName()
        << ", ����� #: " << room.getRoomNumber()
        << ", ��: " << checkInDate
        << " ��: " << checkOutDate
        << ", ������: " << status
        << std::endl;
}

std::string Booking::toString() const {
    return std::to_string(bookingID) + "," + std::to_string(guestId) + "," + std::to_string(roomNumber) + "," +
        checkInDate + "," + checkOutDate + "," + status;
}

Booking Booking::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string bidStr, gidStr, rnStr, inDate, outDate, st;
    std::getline(ss, bidStr, ',');
    std::getline(ss, gidStr, ',');
    std::getline(ss, rnStr, ',');
    std::getline(ss, inDate, ',');
    std::getline(ss, outDate, ',');
    std::getline(ss, st); // ������ �� ����� ������

    int bid = 0;
    if (!bidStr.empty()) bid = std::stoi(bidStr);
    int gid = 0;
    if (!gidStr.empty()) gid = std::stoi(gidStr);
    int rn = 0;
    if (!rnStr.empty()) rn = std::stoi(rnStr);

    return Booking(bid, gid, rn, inDate, outDate, st);
}