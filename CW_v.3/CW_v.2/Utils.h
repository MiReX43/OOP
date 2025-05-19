#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Guest.h"
#include "RoomCategory.h"
#include "Room.h"
#include "Employee.h"
#include "Booking.h"
#include "Payment.h"

using namespace std;
// Объявления функций поиска
RoomCategory* findCategoryById(vector<RoomCategory>& categories, int id);
Room* findRoomByNumber(vector<Room>& rooms, int number);
Guest* findGuestById(vector<Guest>& guests, int id);
Booking* findBookingById(vector<Booking>& bookings, int id);
// Employee* findEmployeeById(vector<Employee>& employees, int id); // Если понадобится

// Объявления функций загрузки/сохранения всех данных
void loadAllData(
    vector<Guest>& guests,
    vector<RoomCategory>& categories,
    vector<Room>& rooms,
    vector<Employee>& employees,
    vector<Booking>& bookings,
    vector<Payment>& payments
);

void saveAllData(
    const vector<Guest>& guests,
    const vector<RoomCategory>& categories,
    const vector<Room>& rooms,
    const vector<Employee>& employees,
    const vector<Booking>& bookings,
    const vector<Payment>& payments
);

#endif // UTILS_H