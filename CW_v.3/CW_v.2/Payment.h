#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <sstream> // Для fromString
#include "Booking.h" // Нужно для конструктора и printReceipt

class Payment {
    int paymentID;
    int bookingID_fk; // Явное указание на внешний ключ
    double amount;
    std::string paymentDate;
    std::string paymentMethod;

public:
    static int paymentCounter; // Статический счетчик

    // Конструктор для загрузки из файла
    Payment(int pid, int bid, double amt, std::string method, std::string date);
    // Конструктор для нового платежа
    Payment(const Booking& b, double amt, std::string method, std::string date);

    int getPaymentID() const; // Добавим getter
    int getBookingID() const; // Добавим getter

    void processPayment() const; // Сделаем const, т.к. он только выводит информацию
    void printReceipt() const;

    std::string toString() const;
    static Payment fromString(const std::string& line);
};

#endif // PAYMENT_H