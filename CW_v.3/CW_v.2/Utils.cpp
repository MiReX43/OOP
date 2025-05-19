#include "Utils.h"
#include "FileManager.h" // ��� saveToFile, loadFromFile


// --- ���������� ������� ������ ---

RoomCategory* findCategoryById(std::vector<RoomCategory>& categories, int id) {
    for (auto& cat : categories) {
        if (cat.getId() == id)
            return &cat;
    }
    return nullptr;
}

Room* findRoomByNumber(std::vector<Room>& rooms, int number) {
    for (auto& r : rooms) {
        if (r.getRoomNumber() == number)
            return &r;
    }
    return nullptr;
}

Guest* findGuestById(std::vector<Guest>& guests, int id) {
    for (auto& g : guests) {
        if (g.getId() == id)
            return &g;
    }
    return nullptr;
}

Booking* findBookingById(std::vector<Booking>& bookings, int id) {
    for (auto& b : bookings) {
        if (b.getID() == id)
            return &b;
    }
    return nullptr;
}

// --- ���������� ������� ��������/���������� ���� ������ ---

void loadAllData(
    std::vector<Guest>& guests,
    std::vector<RoomCategory>& categories,
    std::vector<Room>& rooms,
    std::vector<Employee>& employees,
    std::vector<Booking>& bookings,
    std::vector<Payment>& payments) {

    loadFromFile<Guest>("Guest.txt", guests);
    // ����� �������� ������, �������� �������, ���� �� ������������ ��� ��������� ����� ID
    if (!guests.empty()) {
        int maxId = 0;
        for (const auto& g : guests) {
            if (g.getId() > maxId) maxId = g.getId();
        }
        Guest::guestCounter = maxId + 1;
    }


    loadFromFile<RoomCategory>("RoomCategory.txt", categories);
    if (!categories.empty()) {
        int maxId = 0;
        for (const auto& c : categories) {
            if (c.getId() > maxId) maxId = c.getId();
        }
        RoomCategory::categoryCounter = maxId + 1;
    }

    loadFromFile<Room>("Room.txt", rooms);
    if (!rooms.empty()) {
        int maxId = 0;
        for (const auto& r : rooms) {
            if (r.getRoomNumber() > maxId) maxId = r.getRoomNumber(); // Assuming room numbers are like IDs
        }
        Room::roomCounter = maxId + 1;
    }

    loadFromFile<Employee>("Employee.txt", employees);
    if (!employees.empty()) {
        int maxId = 0;
        for (const auto& e : employees) {
            if (e.getId() > maxId) maxId = e.getId();
        }
        Employee::employeeCounter = maxId + 1;
    }

    loadFromFile<Booking>("Booking.txt", bookings);
    if (!bookings.empty()) {
        int maxId = 0;
        for (const auto& b : bookings) {
            if (b.getID() > maxId) maxId = b.getID();
        }
        Booking::bookingCounter = maxId + 1;
    }

    loadFromFile<Payment>("Payment.txt", payments);
    if (!payments.empty()) {
        int maxId = 0;
        for (const auto& p : payments) {
            if (p.getPaymentID() > maxId) maxId = p.getPaymentID();
        }
        Payment::paymentCounter = maxId + 1;
    }
}

void saveAllData(
    const std::vector<Guest>& guests,
    const std::vector<RoomCategory>& categories,
    const std::vector<Room>& rooms,
    const std::vector<Employee>& employees,
    const std::vector<Booking>& bookings,
    const std::vector<Payment>& payments) {

    saveToFile<Guest>("Guest.txt", guests);
    saveToFile<RoomCategory>("RoomCategory.txt", categories);
    saveToFile<Room>("Room.txt", rooms);
    saveToFile<Employee>("Employee.txt", employees);
    saveToFile<Booking>("Booking.txt", bookings);
    saveToFile<Payment>("Payment.txt", payments);
}