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


// ���������� ������� ����
void showMainMenu();
void guestMenu(std::vector<Guest>& guests);
void roomMenu(std::vector<Room>& rooms, std::vector<RoomCategory>& categories);
void categorySubMenu(std::vector<RoomCategory>& categories); // ������������� �� categoryMenu
void editServicesMenu(std::vector<RoomCategory>& categories);
void bookingMenu(std::vector<Guest>& guests, std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<RoomCategory>& categories);
void paymentMenu(std::vector<Booking>& bookings, std::vector<Payment>& payments, const std::vector<Room>& rooms); // �������� rooms ��� ������� ���������
void employeeMenu(std::vector<Employee>& employees);

#endif // MENU_H