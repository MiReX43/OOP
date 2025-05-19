#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sstream> // Для fromString
#include "Guest.h" // Необходимы полные определения для конструктора и display
#include "Room.h"  // Аналогично
using namespace std;
class Booking {
    int bookingID;
    int guestId;
    int roomNumber;
    string checkInDate;
    string checkOutDate;
    string status; // Например: "Активно", "Отменено", "Завершено"

public:
    static int bookingCounter; // Статический счетчик

    // Конструктор для загрузки из файла
    Booking(int id, int gid, int rn, string in, string out, string st);
    // Конструктор для нового бронирования
    Booking(const Guest& g, const Room& r, string in, string out);

    int getID() const;
    int getGuestId() const;
    int getRoomNumber() const;
    string getCheckInDate() const;  // Добавим getter
    string getCheckOutDate() const; // Добавим getter
    string getStatus() const;

    void confirmBooking();
    void cancelBooking();
    void completeBooking(); // Переименовано из completBooking

    double calculateCost(double pricePerNight) const; // Пока остается с фиксированным количеством дней
    void display(const Guest& guest, const Room& room) const; // Передаем по ссылке

    string toString() const;
    static Booking fromString(const string& line);
};

#endif // BOOKING_H