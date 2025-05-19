#ifndef MENU_H
#define MENU_H

#include <vector>
// Включаем все необходимые классы, так как меню с ними работает
#include "Guest.h"
#include "Room.h"
#include "RoomCategory.h"
#include "Booking.h"
#include "Payment.h"
#include "Employee.h"

using namespace std;

// Объявления функций меню
void showMainMenu();
void guestMenu(vector<Guest>& guests);
void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories);
void categorySubMenu(vector<RoomCategory>& categories); // Переименовано из categoryMenu
void editServicesMenu(vector<RoomCategory>& categories);
void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories);
void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments, const vector<Room>& rooms); // Добавили rooms для расчета стоимости
void employeeMenu(vector<Employee>& employees);

#endif // MENU_H