#ifndef MENU_H
#define MENU_H

#include <vector>
// �������� ��� ����������� ������, ��� ��� ���� � ���� ��������
#include "Guest.h"
#include "Room.h"
#include "RoomCategory.h"
#include "Booking.h"
#include "Payment.h"
#include "Employee.h"

using namespace std;

// ���������� ������� ����
void showMainMenu();
void guestMenu(vector<Guest>& guests);
void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories);
void categorySubMenu(vector<RoomCategory>& categories); // ������������� �� categoryMenu
void editServicesMenu(vector<RoomCategory>& categories);
void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories);
void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments, const vector<Room>& rooms); // �������� rooms ��� ������� ���������
void employeeMenu(vector<Employee>& employees);

#endif // MENU_H