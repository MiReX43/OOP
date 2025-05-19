#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <sstream> // ��� fromString
#include "Booking.h" // ����� ��� ������������ � printReceipt

class Payment {
    int paymentID;
    int bookingID_fk; // ����� �������� �� ������� ����
    double amount;
    std::string paymentDate;
    std::string paymentMethod;

public:
    static int paymentCounter; // ����������� �������

    // ����������� ��� �������� �� �����
    Payment(int pid, int bid, double amt, std::string method, std::string date);
    // ����������� ��� ������ �������
    Payment(const Booking& b, double amt, std::string method, std::string date);

    int getPaymentID() const; // ������� getter
    int getBookingID() const; // ������� getter

    void processPayment() const; // ������� const, �.�. �� ������ ������� ����������
    void printReceipt() const;

    std::string toString() const;
    static Payment fromString(const std::string& line);
};

#endif // PAYMENT_H