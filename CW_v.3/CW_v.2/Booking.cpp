#include "Booking.h"
#include <iostream> // Для cout


int Booking::bookingCounter = 1; // Инициализация

// Конструктор для загрузки из файла
Booking::Booking(int id, int gid, int rn, std::string in, std::string out, std::string st)
    : bookingID(id), guestId(gid), roomNumber(rn),
    checkInDate(std::move(in)), checkOutDate(std::move(out)), status(std::move(st)) {
    if (id >= bookingCounter) bookingCounter = id + 1;
}

// Конструктор для нового бронирования
Booking::Booking(const Guest& g, const Room& r, std::string in, std::string out)
    : bookingID(bookingCounter++), guestId(g.getId()), roomNumber(r.getRoomNumber()),
    checkInDate(std::move(in)), checkOutDate(std::move(out)), status("Активно") {
}

int Booking::getID() const { return bookingID; }
int Booking::getGuestId() const { return guestId; }
int Booking::getRoomNumber() const { return roomNumber; }
std::string Booking::getCheckInDate() const { return checkInDate; }
std::string Booking::getCheckOutDate() const { return checkOutDate; }
std::string Booking::getStatus() const { return status; }

void Booking::confirmBooking() { status = "Активно"; }
void Booking::cancelBooking() { status = "Отменено"; }
void Booking::completeBooking() { status = "Завершено"; }

// TODO: Реализовать корректный расчет стоимости на основе дат
double Booking::calculateCost(double pricePerNight) const {
    // Пока что заглушка, нужно будет реализовать расчет количества ночей
    // Например, можно использовать std::tm и mktime для разницы дат
    return 3.0 * pricePerNight; // Фиксированное количество ночей для примера
}

void Booking::display(const Guest& guest, const Room& room) const {
    std::cout << "ID бронирования: " << bookingID
        << ", Гость: " << guest.getName()
        << ", Номер #: " << room.getRoomNumber()
        << ", От: " << checkInDate
        << " До: " << checkOutDate
        << ", Статус: " << status
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
    std::getline(ss, st); // Статус до конца строки

    int bid = 0;
    if (!bidStr.empty()) bid = std::stoi(bidStr);
    int gid = 0;
    if (!gidStr.empty()) gid = std::stoi(gidStr);
    int rn = 0;
    if (!rnStr.empty()) rn = std::stoi(rnStr);

    return Booking(bid, gid, rn, inDate, outDate, st);
}