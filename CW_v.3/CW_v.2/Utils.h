#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Guest.h"
#include "RoomCategory.h"
#include "Room.h"
#include "Employee.h"
#include "Booking.h"
#include "Payment.h"


// Объявления функций поиска
RoomCategory* findCategoryById(std::vector<RoomCategory>& categories, int id);
Room* findRoomByNumber(std::vector<Room>& rooms, int number);
Guest* findGuestById(std::vector<Guest>& guests, int id);
Booking* findBookingById(std::vector<Booking>& bookings, int id);
// Employee* findEmployeeById(std::vector<Employee>& employees, int id); // Если понадобится

// Объявления функций загрузки/сохранения всех данных
void loadAllData(
    std::vector<Guest>& guests,
    std::vector<RoomCategory>& categories,
    std::vector<Room>& rooms,
    std::vector<Employee>& employees,
    std::vector<Booking>& bookings,
    std::vector<Payment>& payments
);

void saveAllData(
    const std::vector<Guest>& guests,
    const std::vector<RoomCategory>& categories,
    const std::vector<Room>& rooms,
    const std::vector<Employee>& employees,
    const std::vector<Booking>& bookings,
    const std::vector<Payment>& payments
);

#endif // UTILS_H