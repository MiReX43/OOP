#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sstream> // Для fromString

#include "Guest.h" // Необходимы полные определения для конструктора и display
#include "Room.h"  // Аналогично

class Booking {
    int bookingID;
    int guestId;
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    std::string status; // Например: "Активно", "Отменено", "Завершено"

public:
    static int bookingCounter; // Статический счетчик

    // Конструктор для загрузки из файла
    Booking(int id, int gid, int rn, std::string in, std::string out, std::string st);
    // Конструктор для нового бронирования
    Booking(const Guest& g, const Room& r, std::string in, std::string out);

    int getID() const;
    int getGuestId() const;
    int getRoomNumber() const;
    std::string getCheckInDate() const;  // Добавим getter
    std::string getCheckOutDate() const; // Добавим getter
    std::string getStatus() const;

    void confirmBooking();
    void cancelBooking();
    void completeBooking(); // Переименовано из completBooking

    double calculateCost(double pricePerNight) const; // Пока остается с фиксированным количеством дней
    void display(const Guest& guest, const Room& room) const; // Передаем по ссылке

    std::string toString() const;
    static Booking fromString(const std::string& line);
};

#endif // BOOKING_H