#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <sstream> // ��� fromString
#include "Booking.h" // ����� ��� ������������ � printReceipt
using namespace std;
class Payment {
    int paymentID;
    int bookingID_fk; // ����� �������� �� ������� ����
    double amount;
    string paymentDate;
    string paymentMethod;

public:
    static int paymentCounter; // ����������� �������

    // ����������� ��� �������� �� �����
    Payment(int pid, int bid, double amt, string method, string date);
    // ����������� ��� ������ �������
    Payment(const Booking& b, double amt, string method, string date);

    int getPaymentID() const; // ������� getter
    int getBookingID() const; // ������� getter

    void processPayment() const; // ������� const, �.�. �� ������ ������� ����������
    void printReceipt() const;

    string toString() const;
    static Payment fromString(const string& line);
};

#endif // PAYMENT_H