#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>    // Для std::numeric_limits
#include <iomanip>   // Для std::fixed, std::setprecision
#include <sstream>
#include <memory>    // Для std::unique_ptr, если бы использовался
#include <windows.h> // Для SetConsoleCP, SetConsoleOutputCP

#include "Guest.h"
#include "RoomCategory.h"
#include "Room.h"
#include "Employee.h"
#include "Booking.h"
#include "Payment.h"
#include "FileManager.h"
#include "Utils.h"
#include "Menu.h"

// Вспомогательная функция для безопасного ввода числа из main, если нужна здесь
int getMainIntInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    // Не очищаем буфер здесь, если сразу после этого не будет getline
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return choice;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << std::fixed << std::setprecision(2); // Глобальная настройка для вывода double

    std::vector<Guest> guests;
    std::vector<RoomCategory> categories;
    std::vector<Room> rooms;
    std::vector<Employee> employees;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;

    loadAllData(guests, categories, rooms, employees, bookings, payments);

    // Инициализация тестовых данных, если файлы пусты (для первого запуска)
    if (categories.empty()) {
        categories.emplace_back(RoomCategory::categoryCounter++, "Standard", "Стандартный номер", std::vector<std::string>{"WiFi", "Холодильник"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Deluxe", "Номер повышенной комфортности", std::vector<std::string>{"WiFi", "Холодильник", "Кофемашина"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Suite", "Люкс", std::vector<std::string>{"WiFi", "Холодильник", "Кофемашина", "Минибар"});
        // saveToFile<RoomCategory>("RoomCategory.txt", categories); // Можно сохранить сразу
    }

    if (employees.empty()) {
        employees.emplace_back(Employee::employeeCounter++, "Гиревой Д.И", "1234567890", "manager@example.com", "Менеджер");
        // saveToFile<Employee>("Employee.txt", employees);
    }

    if (rooms.empty() && !categories.empty()) { // Добавляем комнаты, только если есть категории
        if (categories.size() > 0) rooms.emplace_back(Room::roomCounter++, categories[0].getId(), 2, true, 2500.00);
        if (categories.size() > 1) rooms.emplace_back(Room::roomCounter++, categories[1].getId(), 3, true, 4800.50);
        if (categories.size() > 2) rooms.emplace_back(Room::roomCounter++, categories[2].getId(), 4, true, 7550.75);
        // saveToFile<Room>("Room.txt", rooms);
    }
    // Важно: после загрузки данных и возможного добавления начальных данных,
    // убедитесь, что статические счетчики в классах обновлены правильно.
    // Это уже делается в loadAllData. Если добавляете данные после loadAllData,
    // как здесь, то счетчики RoomCategory::categoryCounter, Employee::employeeCounter, Room::roomCounter
    // уже будут увеличены при создании объектов.

    int choice;
    do {
        showMainMenu();
        // Безопасный ввод для главного меню
        while (!(std::cin >> choice)) {
            std::cout << "Неверный ввод. Пожалуйста, введите число: ";
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очистка буфера после числа

        switch (choice) {
        case 1:
            guestMenu(guests);
            break;
        case 2:
            roomMenu(rooms, categories);
            break;
        case 3:
            bookingMenu(guests, rooms, bookings, categories);
            break;
        case 4:
            paymentMenu(bookings, payments, rooms);
            break;
        case 5:
            employeeMenu(employees);
            break;
        case 0:
            std::cout << "Сохранение данных и выход из программы..." << std::endl;
            saveAllData(guests, categories, rooms, employees, bookings, payments);
            break;
        default:
            std::cout << "Неверный выбор. Повторите попытку." << std::endl;
        }
    } while (choice != 0);

    return 0;
}