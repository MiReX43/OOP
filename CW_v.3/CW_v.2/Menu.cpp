#include "Menu.h"
#include "Utils.h" // ��� find... �������
#include "FileManager.h" // ��� saveToFile � ������ ���� (���� ����� ��������� ������ ��� ������ �� ��������)
#include <iostream>
#include <limits>    // ��� std::numeric_limits
#include <sstream>   // ��� std::stringstream � editServicesMenu
#define NOMINMAX
#include <windows.h> // ��� SetConsoleCP/OutputCP

// ��������������� ������� ��� ����������� ����� �����
int getIntInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "�������� ����. ����������, ������� �����: ";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ������� ������ ����� �����
    return choice;
}

std::string getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}


void showMainMenu() {
    std::cout << "\n==== ������� ���� ====\n";
    std::cout << "1. �����\n";
    std::cout << "2. ������\n";
    std::cout << "3. ������������\n";
    std::cout << "4. ������\n";
    std::cout << "5. ����������\n";
    std::cout << "0. �����\n";
    std::cout << "�������� ��������: ";
}

void guestMenu(std::vector<Guest>& guests) {
    int choice;
    do {
        std::cout << "\n==== ���� ������ ====\n";
        std::cout << "1. ������� ���������� � ������\n";
        std::cout << "2. �������� ���������� ����������\n";
        std::cout << "0. ����� � ������� ����\n";
        std::cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (guests.empty()) {
                std::cout << "������ ������ ����.\n";
                break;
            }
            for (const auto& g : guests) {
                g.displayInfo();
            }
            break;
        }
        case 2: {
            if (guests.empty()) {
                std::cout << "������ ������ ����.\n";
                break;
            }
            std::cout << "������� �����:\n";
            for (const auto& g : guests) {
                g.displayInfo();
            }
            std::cout << "������� ID ����� ��� ���������: ";
            int id = getIntInput();
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                std::string phone = getStringInput("������� ����� �������: ");
                std::string email = getStringInput("������� ����� email: ");
                guest->updateContactInfo(phone, email);
                std::cout << "���������� ���������� ���������.\n";
            } else {
                std::cout << "����� � ID " << id << " �� ������.\n";
            }
            break;
        }
        case 0:
            saveToFile<Guest>("Guest.txt", guests); // ��������� ��� ������ �� �������
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void roomMenu(std::vector<Room>& rooms, std::vector<RoomCategory>& categories) {
    int choice;
    do {
        std::cout << "\n==== ���� ������� ====\n";
        std::cout << "1. �������� ��� ������\n";
        std::cout << "2. �������� ������ ����������� ������\n";
        std::cout << "3. ����������� ��������� �������\n";
        std::cout << "4. �������� ������ ����� ��� ���������\n";
        std::cout << "0. ����� � ������� ����\n";
        std::cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (rooms.empty()) {
                std::cout << "������ ������� ����.\n";
                break;
            }
            std::cout << "������ �������:\n";
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    std::cout << "Room #: " << r.getRoomNumber() << " (��������� ID: " << r.getCategoryId() << " �� �������)" << std::endl;
            }
            break;
        case 2: {
            if (rooms.empty()) {
                std::cout << "������ ������� ����.\n";
                break;
            }
            std::cout << "������� ������:\n";
             for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat) r.displayDetails(*cat); else std::cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)\n";
            }
            std::cout << "������� ����� ������� ��� ��������� �������: ";
            int number = getIntInput();
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                std::cout << "������� ������: " << (room->getAvailability() ? "��������" : "�����") << std::endl;
                std::cout << "������� ����� ������ (1 - ��������, 0 - �����): ";
                int statusInput = getIntInput();
                if (statusInput == 0 || statusInput == 1) {
                    room->updateStatus(statusInput != 0);
                    std::cout << "������ ��������.\n";
                } else {
                    std::cout << "�������� ���� �������.\n";
                }
            } else {
                std::cout << "������� � ������� " << number << " �� �������.\n";
            }
            break;
        }
        case 3:
            categorySubMenu(categories);
            break;
        case 4:
            editServicesMenu(categories);
            break;
        case 0:
            saveToFile<Room>("Room.txt", rooms);
            saveToFile<RoomCategory>("RoomCategory.txt", categories);
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void categorySubMenu(std::vector<RoomCategory>& categories) {
    std::cout << "\n==== ��������� ������� ====\n";
    if (categories.empty()) {
        std::cout << "��� ��������� �������.\n";
        return;
    }
    for (const auto& c : categories) {
        std::cout << "ID: " << c.getId()
                  << ", ��������: " << c.getName()
                  << ", ��������: " << c.getDescription()
                  << std::endl;
        std::cout << "  ������:\n";
        c.printServices();
    }
}

void editServicesMenu(std::vector<RoomCategory>& categories) {
    if (categories.empty()) {
        std::cout << "��� ��������� ��� ��������������.\n";
        return;
    }
    std::cout << "\n==== �������� ������ ����� ====\n";
    std::cout << "������ ���������:\n";
    for (const auto& c : categories) {
        std::cout << "ID: " << c.getId() << ", ��������: " << c.getName() << std::endl;
    }
    std::cout << "������� ID ��������� ��� ��������� �����: ";
    int id = getIntInput();
    RoomCategory* category = findCategoryById(categories, id);

    if (!category) {
        std::cout << "��������� � ID " << id << " �� �������.\n";
        return;
    }

    std::cout << "������� ������ ��� ��������� '" << category->getName() << "':\n";
    category->printServices();
    
    std::string line = getStringInput("������� ����� ������ ����� ������� (��������: WiFi,�������,�������). ��� �������� ���� ����� ������� ������ ������: ");

    std::vector<std::string> newServices;
    if (!line.empty()) {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            // ������� ������ ������� � ������ � ����� ������
            size_t first = token.find_first_not_of(' ');
            if (std::string::npos == first) { // ���� ������ ����� ��� ������ �� ��������
                continue;
            }
            size_t last = token.find_last_not_of(' ');
            newServices.push_back(token.substr(first, (last - first + 1)));
        }
    }
    category->setServices(newServices);
    std::cout << "������ ����� ��������.\n";
}

void bookingMenu(std::vector<Guest>& guests, std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<RoomCategory>& categories) {
    int choice;
    do {
        std::cout << "\n==== ���� ������������ ====\n";
        std::cout << "1. �������� ��� ������������\n";
        std::cout << "2. ������� ����� ������������\n";
        std::cout << "3. �������� ������������\n";
        std::cout << "0. ����� � ������� ����\n";
        std::cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (bookings.empty()) {
                std::cout << "��� �������� ��� ����������� ������������.\n";
                break;
            }
            std::cout << "������ ������������:\n";
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                } else {
                    std::cout << "������: �� ������� ����� ����� ��� ������� ��� ������������ ID: " << b.getID() << std::endl;
                }
            }
            break;
        }
        case 2: {
            std::string name = getStringInput("������� ��� �����: ");
            std::string phone = getStringInput("�������: ");
            std::string email = getStringInput("Email: ");
            std::string passport = getStringInput("���������� ������: ");
            
            Guest newGuest(Guest::guestCounter, name, phone, email, passport); // ���������� ����������� �������
            guests.push_back(newGuest);
            Guest::guestCounter++; // ����������� ������� ������� ����� ��������� ����������
            saveToFile<Guest>("Guest.txt", guests); // ����� ��������� ������ �����


            std::cout << "��������� ������ ��� ������������:\n";
            bool availableRoomsExist = false;
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat) r.displayDetails(*cat);
                    else std::cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)\n";
                    availableRoomsExist = true;
                }
            }
            if (!availableRoomsExist) {
                std::cout << "��� ��������� ������� ��� ������������.\n";
                // ��������, ����� ������� ������ ��� ���������� �����, ���� ��� �������
                // guests.pop_back(); // �����������������, ���� ����� ������ �����
                break;
            }

            std::cout << "�������� ����� ������� ��� ������������: ";
            int roomNumber = getIntInput();
            Room* selectedRoom = findRoomByNumber(rooms, roomNumber);

            if (!selectedRoom || !selectedRoom->getAvailability()) {
                std::cout << "������� �� ������� ��� ��� ������.\n";
                // guests.pop_back(); // ���� ����� ���������� ������ ��� ����� ������������
                break;
            }

            std::string checkIn = getStringInput("���� ������ (��.��.����): ");
            std::string checkOut = getStringInput("���� ������ (��.��.����): ");

            Booking newBooking(newGuest, *selectedRoom, checkIn, checkOut);
            // newBooking.confirmBooking(); // ������ "�������" ��� ��������������� � ������������
            selectedRoom->updateStatus(false); // ������� ���������� �����������
            bookings.push_back(newBooking);
            
            std::cout << "������������ ������� �������. ID ������������: " << newBooking.getID() << std::endl;
            break;
        }
        case 3: {
            if (bookings.empty()) {
                std::cout << "��� ������������ ��� ������.\n";
                break;
            }
            std::cout << "�������� ������������:\n";
            bool activeBookingsExist = false;
            for (const auto& b : bookings) {
                 if (b.getStatus() == "�������") {
                    Guest* guest = findGuestById(guests, b.getGuestId());
                    Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                    if (guest && room) b.display(*guest, *room);
                    activeBookingsExist = true;
                 }
            }
            if (!activeBookingsExist) {
                 std::cout << "��� �������� ������������ ��� ������.\n";
                 break;
            }

            std::cout << "������� ID ������������ ��� ������: ";
            int id = getIntInput();
            Booking* bookingToCancel = findBookingById(bookings, id);

            if (bookingToCancel && bookingToCancel->getStatus() == "�������") {
                Room* roomToFree = findRoomByNumber(rooms, bookingToCancel->getRoomNumber());
                if (roomToFree) {
                    roomToFree->updateStatus(true); // ������� ����� ��������
                }
                bookingToCancel->cancelBooking(); // ������ ������ ������������
                std::cout << "������������ ID " << id << " ��������.\n";
            } else {
                std::cout << "������������ � ID " << id << " �� ������� ��� �� �������� ��������.\n";
            }
            break;
        }
        case 0:
            saveToFile<Booking>("Booking.txt", bookings);
            saveToFile<Room>("Room.txt", rooms); // ������ ������ ��� ����������
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void paymentMenu(std::vector<Booking>& bookings, std::vector<Payment>& payments, const std::vector<Room>& rooms) {
    int choice;
    do {
        std::cout << "\n==== ���� ������ ====\n";
        std::cout << "1. �������� ������ �� ������������\n";
        std::cout << "2. �������� ��� ��������� �� ������\n";
        std::cout << "0. ����� � ������� ����\n";
        std::cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            std::cout << "�������� ������������ ��� ������:\n";
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() == "�������") { // ���������� ����� ������ ��������
                     // ��� ����������� ������� ����� ������������� ������ guests
                    std::cout << "ID ������������: " << b.getID() 
                              << ", ����� �������: " << b.getRoomNumber() 
                              //<< ", ����� ID: " << b.getGuestId() // ���� ����� ������ ����������
                              << std::endl;
                    activeBookingExists = true;
                }
            }
            if (!activeBookingExists) {
                std::cout << "��� �������� ������������ ��� ������.\n";
                break;
            }

            std::cout << "������� ID ������������ ��� ������: ";
            int bookingId = getIntInput();
            Booking* bookingToPay = findBookingById(bookings, bookingId);

            if (bookingToPay && bookingToPay->getStatus() == "�������") {
                const Room* roomOfBooking = nullptr;
                for(const auto& r : rooms){
                    if(r.getRoomNumber() == bookingToPay->getRoomNumber()){
                        roomOfBooking = &r;
                        break;
                    }
                }

                double cost = 0.0;
                if (roomOfBooking) {
                     // ����� ����� �������� ������ �������, ���� calculateCost ����� ������������ ���� �� bookingToPay
                    cost = bookingToPay->calculateCost(roomOfBooking->getPrice()); 
                    std::cout << "��������������� ��������� ����������: " << cost << " ���." << std::endl;
                } else {
                    std::cout << "������: �� ������� ����� ������� ��� ������� ���������." << std::endl;
                    // ����� ���������� ������ ����� ������� ��� �������� ��������
                }


                std::cout << "������� ����� ������: ";
                double amount;
                while (!(std::cin >> amount) || amount <= 0) {
                    std::cout << "�������� �����. ������� ������������� �����: ";
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');


                std::string method = getStringInput("������� ������ ������ (��������, �����): ");
                std::string date = getStringInput("������� ���� ������ (��.��.����): ");

                Payment newPayment(*bookingToPay, amount, method, date);
                newPayment.processPayment(); // ����� ���������� �� ���������
                payments.push_back(newPayment);
                
                bookingToPay->completeBooking(); // ������ ������ ������������ �� "���������"
                // ������ ������� (isAvailable) �� ������, �.�. ��� ����� ���� ������������� ��������� ������.
                // ������������ ������� ������ ����������� ��� ������ (��� ������).
                // ���� "���������" ��������, ��� ����� ������, �� ������� ����� ����������.
                // Room* roomToUpdate = findRoomByNumber(rooms, bookingToPay->getRoomNumber());
                // if(roomToUpdate) roomToUpdate->updateStatus(true);


                std::cout << "������ ���������. ������ ������������ ID " << bookingId << " ������� �� '���������'.\n";
            } else {
                std::cout << "������������ � ID " << bookingId << " �� ������� ��� �� �������� �������� ��� ������.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                std::cout << "��������� �� ������ ���.\n";
                break;
            }
            std::cout << "��� ��������� �� ������:\n";
            for (const auto& p : payments) {
                p.printReceipt();
            }
            break;
        }
        case 0:
            saveToFile<Payment>("Payment.txt", payments);
            saveToFile<Booking>("Booking.txt", bookings); // ������ ������������ ��� ����������
            // saveToFile<Room>("Room.txt", rooms); // ���� ������ ������ ������
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void employeeMenu(std::vector<Employee>& employees) {
    // � ������������ ���� ��� ���� ������ �������� ������ � ������.
    // ������� ��� ����� ��������������, ���� �����������.
    // ���� ��� ������� ��� ���� ��� ������������.
    // TODO: ����������� ����������� ���� ��� ����������� (����������, ��������, ��������������)
    int choice;
     do {
        std::cout << "\n==== ���� ����������� ====\n";
        std::cout << "1. �������� ���� �����������\n";
        std::cout << "2. �������� ������ ����������\n";
        // �������� ������ �����: �������, �������������...
        std::cout << "0. ����� � ������� ����\n";
        std::cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (employees.empty()) {
                std::cout << "������ ����������� ����.\n";
            } else {
                std::cout << "������ �����������:\n";
                for (const auto& e : employees) {
                    e.displayInfo();
                }
            }
            break;
        case 2: {
            std::string name = getStringInput("������� ��� ����������: ");
            std::string phone = getStringInput("�������: ");
            std::string email = getStringInput("Email: ");
            std::string position = getStringInput("���������: ");

            Employee newEmployee(Employee::employeeCounter, name, phone, email, position);
            employees.push_back(newEmployee);
            Employee::employeeCounter++;
            std::cout << "��������� ��������. ID: " << newEmployee.getId() << std::endl;
            break;
        }
        case 0:
            saveToFile<Employee>("Employee.txt", employees);
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
    
}