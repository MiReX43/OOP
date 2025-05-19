#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>    // ��� numeric_limits
#include <iomanip>   // ��� fixed, setprecision
#include <sstream>
#include <memory>    // ��� unique_ptr, ���� �� �������������
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

using namespace std;

// ��������������� ������� ��� ����������� ����� ����� �� main, ���� ����� �����
int getMainIntInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "�������� ����. ����������, ������� �����: ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
    // �� ������� ����� �����, ���� ����� ����� ����� �� ����� getline
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return choice;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << fixed << setprecision(2); // ���������� ��������� ��� ������ double

    vector<Guest> guests;
    vector<RoomCategory> categories;
    vector<Room> rooms;
    vector<Employee> employees;
    vector<Booking> bookings;
    vector<Payment> payments;

    loadAllData(guests, categories, rooms, employees, bookings, payments);

    // ������������� �������� ������, ���� ����� ����� (��� ������� �������)
    if (categories.empty()) {
        categories.emplace_back(RoomCategory::categoryCounter++, "Standard", "����������� �����", vector<string>{"WiFi", "�����������"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Deluxe", "����� ���������� ������������", vector<string>{"WiFi", "�����������", "����������"});
        categories.emplace_back(RoomCategory::categoryCounter++, "Suite", "����", vector<string>{"WiFi", "�����������", "����������", "�������"});
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
        while (!(cin >> choice)) {
            cout << "�������� ����. ����������, ������� �����: ";
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // ������� ������ ����� �����

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
            cout << "���������� ������ � ����� �� ���������..." << endl;
            saveAllData(guests, categories, rooms, employees, bookings, payments);
            break;
        default:
            cout << "�������� �����. ��������� �������." << endl;
        }
    } while (choice != 0);

    return 0;
}