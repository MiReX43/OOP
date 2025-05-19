#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>    // ��� std::numeric_limits
#include <iomanip>   // ��� std::fixed, std::setprecision
#include <sstream>
#include <memory>    // ��� std::unique_ptr, ���� �� �������������
#include <windows.h> // ��� SetConsoleCP, SetConsoleOutputCP

#include "Guest.h"
#include "RoomCategory.h"
#include "Room.h"
#include "Employee.h"
#include "Booking.h"
#include "Payment.h"
#include "FileManager.h"
#include "Utils.h"
#include "Menu.h"

// ��������������� ������� ��� ����������� ����� ����� �� main, ���� ����� �����
int getMainIntInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "�������� ����. ����������, ������� �����: ";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    // �� ������� ����� �����, ���� ����� ����� ����� �� ����� getline
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return choice;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << std::fixed << std::setprecision(2); // ���������� ��������� ��� ������ double

    std::vector<Guest> guests;
    std::vector<RoomCategory> categories;
    std::vector<Room> rooms;
    std::vector<Employee> employees;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;

    loadAllData(guests, categories, rooms, employees, bookings, payments);

    // ������������� �������� ������, ���� ����� ����� (��� ������� �������)
    if (categories.empty()) {
        categories.emplace_back(RoomCategory::categoryCounter++, "Standard", "����������� �����", std::vector<std::string>{"WiFi", "�����������"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Deluxe", "����� ���������� ������������", std::vector<std::string>{"WiFi", "�����������", "����������"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Suite", "����", std::vector<std::string>{"WiFi", "�����������", "����������", "�������"});
        // saveToFile<RoomCategory>("RoomCategory.txt", categories); // ����� ��������� �����
    }

    if (employees.empty()) {
        employees.emplace_back(Employee::employeeCounter++, "������� �.�", "1234567890", "manager@example.com", "��������");
        // saveToFile<Employee>("Employee.txt", employees);
    }

    if (rooms.empty() && !categories.empty()) { // ��������� �������, ������ ���� ���� ���������
        if (categories.size() > 0) rooms.emplace_back(Room::roomCounter++, categories[0].getId(), 2, true, 2500.00);
        if (categories.size() > 1) rooms.emplace_back(Room::roomCounter++, categories[1].getId(), 3, true, 4800.50);
        if (categories.size() > 2) rooms.emplace_back(Room::roomCounter++, categories[2].getId(), 4, true, 7550.75);
        // saveToFile<Room>("Room.txt", rooms);
    }
    // �����: ����� �������� ������ � ���������� ���������� ��������� ������,
    // ���������, ��� ����������� �������� � ������� ��������� ���������.
    // ��� ��� �������� � loadAllData. ���� ���������� ������ ����� loadAllData,
    // ��� �����, �� �������� RoomCategory::categoryCounter, Employee::employeeCounter, Room::roomCounter
    // ��� ����� ��������� ��� �������� ��������.

    int choice;
    do {
        showMainMenu();
        // ���������� ���� ��� �������� ����
        while (!(std::cin >> choice)) {
            std::cout << "�������� ����. ����������, ������� �����: ";
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ������� ������ ����� �����

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
            std::cout << "���������� ������ � ����� �� ���������..." << std::endl;
            saveAllData(guests, categories, rooms, employees, bookings, payments);
            break;
        default:
            std::cout << "�������� �����. ��������� �������." << std::endl;
        }
    } while (choice != 0);

    return 0;
}