#include "Payment.h"
#include <iostream> // Для cout
#include <iomanip>  // Для форматирования суммы


int Payment::paymentCounter = 1; // Инициализация

Payment::Payment(int pid, int bid, double amt, std::string method, std::string date)
    : paymentID(pid), bookingID_fk(bid), amount(amt),
    paymentMethod(std::move(method)), paymentDate(std::move(date)) {
    if (pid >= paymentCounter) paymentCounter = pid + 1;
}

Payment::Payment(const Booking& b, double amt, std::string method, std::string date)
    : paymentID(paymentCounter++), bookingID_fk(b.getID()), amount(amt),
    paymentMethod(std::move(method)), paymentDate(std::move(date)) {
}

int Payment::getPaymentID() const { return paymentID; }
int Payment::getBookingID() const { return bookingID_fk; }


void Payment::processPayment() const {
    std::cout << "Обработка платежа ID " << paymentID
        << " для бронирования ID " << bookingID_fk
        << " в размере " << std::fixed << std::setprecision(2) << amount << " руб. используя " << paymentMethod << std::endl;
}

void Payment::printReceipt() const {
    std::cout << "ID Квитанции: " << paymentID
        << ", ID бронирования: " << bookingID_fk
        << ", Сумма: " << std::fixed << std::setprecision(2) << amount << " руб."
        << ", Дата: " << paymentDate
        << ", Способ оплаты: " << paymentMethod
        << std::endl;
}

std::string Payment::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    return std::to_string(paymentID) + "," + std::to_string(bookingID_fk) + "," + oss.str() + "," + paymentMethod + "," + paymentDate;
}

Payment Payment::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string pidStr, bidStr, amtStr, method, date;
    std::getline(ss, pidStr, ',');
    std::getline(ss, bidStr, ',');
    std::getline(ss, amtStr, ',');
    std::getline(ss, method, ',');
    std::getline(ss, date, ',');

    int pid = 0;
    if (!pidStr.empty()) pid = std::stoi(pidStr);
    int bid = 0;
    if (!bidStr.empty()) bid = std::stoi(bidStr); // Исправлено: было pidStr
    double amt = 0.0;
    if (!amtStr.empty()) amt = std::stod(amtStr);

    return Payment(pid, bid, amt, method, date);
}