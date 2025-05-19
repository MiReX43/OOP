#include "Payment.h"
#include <iostream> // ��� cout
#include <iomanip>  // ��� �������������� �����

using namespace std;
int Payment::paymentCounter = 1; // �������������

Payment::Payment(int pid, int bid, double amt, string method, string date)
    : paymentID(pid), bookingID_fk(bid), amount(amt),
    paymentMethod(move(method)), paymentDate(move(date)) {
    if (pid >= paymentCounter) paymentCounter = pid + 1;
}

Payment::Payment(const Booking& b, double amt, string method, string date)
    : paymentID(paymentCounter++), bookingID_fk(b.getID()), amount(amt),
    paymentMethod(move(method)), paymentDate(move(date)) {
}

int Payment::getPaymentID() const { return paymentID; }
int Payment::getBookingID() const { return bookingID_fk; }


void Payment::processPayment() const {
    cout << "��������� ������� ID " << paymentID
        << " ��� ������������ ID " << bookingID_fk
        << " � ������� " << fixed << setprecision(2) << amount << " ���. ��������� " << paymentMethod << endl;
}

void Payment::printReceipt() const {
    cout << "ID ���������: " << paymentID
        << ", ID ������������: " << bookingID_fk
        << ", �����: " << fixed << setprecision(2) << amount << " ���."
        << ", ����: " << paymentDate
        << ", ������ ������: " << paymentMethod
        << endl;
}

string Payment::toString() const {
    ostringstream oss;
    oss << fixed << setprecision(2) << amount;
    return to_string(paymentID) + "," + to_string(bookingID_fk) + "," + oss.str() + "," + paymentMethod + "," + paymentDate;
}

Payment Payment::fromString(const string& line) {
    stringstream ss(line);
    string pidStr, bidStr, amtStr, method, date;
    getline(ss, pidStr, ',');
    getline(ss, bidStr, ',');
    getline(ss, amtStr, ',');
    getline(ss, method, ',');
    getline(ss, date, ',');

    int pid = 0;
    if (!pidStr.empty()) pid = stoi(pidStr);
    int bid = 0;
    if (!bidStr.empty()) bid = stoi(bidStr); // ����������: ���� pidStr
    double amt = 0.0;
    if (!amtStr.empty()) amt = stod(amtStr);

    return Payment(pid, bid, amt, method, date);
}