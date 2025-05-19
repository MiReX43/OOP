#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <sstream> // Для fromString
#include "Booking.h" // Нужно для конструктора и printReceipt
using namespace std;
class Payment {
    int paymentID;
    int bookingID_fk; // Явное указание на внешний ключ
    double amount;
    string paymentDate;
    string paymentMethod;

public:
    static int paymentCounter; // Статический счетчик

    // Конструктор для загрузки из файла
    Payment(int pid, int bid, double amt, string method, string date);
    // Конструктор для нового платежа
    Payment(const Booking& b, double amt, string method, string date);

    int getPaymentID() const; // Добавим getter
    int getBookingID() const; // Добавим getter

    void processPayment() const; // Сделаем const, т.к. он только выводит информацию
    void printReceipt() const;

    string toString() const;
    static Payment fromString(const string& line);
};

#endif // PAYMENT_H