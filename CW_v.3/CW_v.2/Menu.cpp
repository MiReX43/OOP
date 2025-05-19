#include "Menu.h"
#include "Utils.h" // ��� find... �������
#include "FileManager.h" // ��� saveToFile � ������ ���� (���� ����� ��������� ������ ��� ������ �� ��������)
#include <iostream>
#include <limits>    // ��� numeric_limits
#include <sstream>   // ��� stringstream � editServicesMenu
#define NOMINMAX
#include <windows.h> // ��� SetConsoleCP/OutputCP

using namespace std;

// ��������������� ������� ��� ����������� ����� �����
int getIntInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "�������� ����. ����������, ������� �����: ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
    cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // ������� ������ ����� �����
    return choice;
}

string getStringInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}


void showMainMenu() {
    cout << "\n==== ������� ���� ====\n";
    cout << "1. �����\n";
    cout << "2. ������\n";
    cout << "3. ������������\n";
    cout << "4. ������\n";
    cout << "5. ����������\n";
    cout << "0. �����\n";
    cout << "�������� ��������: ";
}

void guestMenu(vector<Guest>& guests) {
    int choice;
    do {
        cout << "\n==== ���� ������ ====\n";
        cout << "1. ������� ���������� � ������\n";
        cout << "2. �������� ���������� ����������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (guests.empty()) {
                cout << "������ ������ ����.\n";
                break;
            }
            for (const auto& g : guests) {
                g.displayInfo();
            }
            break;
        }
        case 2: {
            if (guests.empty()) {
                cout << "������ ������ ����.\n";
                break;
            }
            cout << "������� �����:\n";
            for (const auto& g : guests) {
                g.displayInfo();
            }
            cout << "������� ID ����� ��� ���������: ";
            int id = getIntInput();
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                string phone = getStringInput("������� ����� �������: ");
                string email = getStringInput("������� ����� email: ");
                guest->updateContactInfo(phone, email);
                cout << "���������� ���������� ���������.\n";
            } else {
                cout << "����� � ID " << id << " �� ������.\n";
            }
            break;
        }
        case 0:
            saveToFile<Guest>("Guest.txt", guests); // ��������� ��� ������ �� �������
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== ���� ������� ====\n";
        cout << "1. �������� ��� ������\n";
        cout << "2. �������� ������ ����������� ������\n";
        cout << "3. ����������� ��������� �������\n";
        cout << "4. �������� ������ ����� ��� ���������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (rooms.empty()) {
                cout << "������ ������� ����.\n";
                break;
            }
            cout << "������ �������:\n";
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (��������� ID: " << r.getCategoryId() << " �� �������)" << endl;
            }
            break;
        case 2: {
            if (rooms.empty()) {
                cout << "������ ������� ����.\n";
                break;
            }
            cout << "������� ������:\n";
             for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat) r.displayDetails(*cat); else cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)\n";
            }
            cout << "������� ����� ������� ��� ��������� �������: ";
            int number = getIntInput();
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                cout << "������� ������: " << (room->getAvailability() ? "��������" : "�����") << endl;
                cout << "������� ����� ������ (1 - ��������, 0 - �����): ";
                int statusInput = getIntInput();
                if (statusInput == 0 || statusInput == 1) {
                    room->updateStatus(statusInput != 0);
                    cout << "������ ��������.\n";
                } else {
                    cout << "�������� ���� �������.\n";
                }
            } else {
                cout << "������� � ������� " << number << " �� �������.\n";
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
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void categorySubMenu(vector<RoomCategory>& categories) {
    cout << "\n==== ��������� ������� ====\n";
    if (categories.empty()) {
        cout << "��� ��������� �������.\n";
        return;
    }
    for (const auto& c : categories) {
        cout << "ID: " << c.getId()
                  << ", ��������: " << c.getName()
                  << ", ��������: " << c.getDescription()
                  << endl;
        cout << "  ������:\n";
        c.printServices();
    }
}

void editServicesMenu(vector<RoomCategory>& categories) {
    if (categories.empty()) {
        cout << "��� ��������� ��� ��������������.\n";
        return;
    }
    cout << "\n==== �������� ������ ����� ====\n";
    cout << "������ ���������:\n";
    for (const auto& c : categories) {
        cout << "ID: " << c.getId() << ", ��������: " << c.getName() << endl;
    }
    cout << "������� ID ��������� ��� ��������� �����: ";
    int id = getIntInput();
    RoomCategory* category = findCategoryById(categories, id);

    if (!category) {
        cout << "��������� � ID " << id << " �� �������.\n";
        return;
    }

    cout << "������� ������ ��� ��������� '" << category->getName() << "':\n";
    category->printServices();
    
    string line = getStringInput("������� ����� ������ ����� ������� (��������: WiFi,�������,�������). ��� �������� ���� ����� ������� ������ ������: ");

    vector<string> newServices;
    if (!line.empty()) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            // ������� ������ ������� � ������ � ����� ������
            size_t first = token.find_first_not_of(' ');
            if (string::npos == first) { // ���� ������ ����� ��� ������ �� ��������
                continue;
            }
            size_t last = token.find_last_not_of(' ');
            newServices.push_back(token.substr(first, (last - first + 1)));
        }
    }
    category->setServices(newServices);
    cout << "������ ����� ��������.\n";
}

void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== ���� ������������ ====\n";
        cout << "1. �������� ��� ������������\n";
        cout << "2. ������� ����� ������������\n";
        cout << "3. �������� ������������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (bookings.empty()) {
                cout << "��� �������� ��� ����������� ������������.\n";
                break;
            }
            cout << "������ ������������:\n";
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                } else {
                    cout << "������: �� ������� ����� ����� ��� ������� ��� ������������ ID: " << b.getID() << endl;
                }
            }
            break;
        }
        case 2: {
            string name = getStringInput("������� ��� �����: ");
            string phone = getStringInput("�������: ");
            string email = getStringInput("Email: ");
            string passport = getStringInput("���������� ������: ");
            
            Guest newGuest(Guest::guestCounter, name, phone, email, passport); // ���������� ����������� �������
            guests.push_back(newGuest);
            Guest::guestCounter++; // ����������� ������� ������� ����� ��������� ����������
            saveToFile<Guest>("Guest.txt", guests); // ����� ��������� ������ �����


            cout << "��������� ������ ��� ������������:\n";
            bool availableRoomsExist = false;
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat) r.displayDetails(*cat);
                    else cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)\n";
                    availableRoomsExist = true;
                }
            }
            if (!availableRoomsExist) {
                cout << "��� ��������� ������� ��� ������������.\n";
                // ��������, ����� ������� ������ ��� ���������� �����, ���� ��� �������
                // guests.pop_back(); // �����������������, ���� ����� ������ �����
                break;
            }

            cout << "�������� ����� ������� ��� ������������: ";
            int roomNumber = getIntInput();
            Room* selectedRoom = findRoomByNumber(rooms, roomNumber);

            if (!selectedRoom || !selectedRoom->getAvailability()) {
                cout << "������� �� ������� ��� ��� ������.\n";
                // guests.pop_back(); // ���� ����� ���������� ������ ��� ����� ������������
                break;
            }

            string checkIn = getStringInput("���� ������ (��.��.����): ");
            string checkOut = getStringInput("���� ������ (��.��.����): ");

            Booking newBooking(newGuest, *selectedRoom, checkIn, checkOut);
            // newBooking.confirmBooking(); // ������ "�������" ��� ��������������� � ������������
            selectedRoom->updateStatus(false); // ������� ���������� �����������
            bookings.push_back(newBooking);
            
            cout << "������������ ������� �������. ID ������������: " << newBooking.getID() << endl;
            break;
        }
        case 3: {
            if (bookings.empty()) {
                cout << "��� ������������ ��� ������.\n";
                break;
            }
            cout << "�������� ������������:\n";
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
                 cout << "��� �������� ������������ ��� ������.\n";
                 break;
            }

            cout << "������� ID ������������ ��� ������: ";
            int id = getIntInput();
            Booking* bookingToCancel = findBookingById(bookings, id);

            if (bookingToCancel && bookingToCancel->getStatus() == "�������") {
                Room* roomToFree = findRoomByNumber(rooms, bookingToCancel->getRoomNumber());
                if (roomToFree) {
                    roomToFree->updateStatus(true); // ������� ����� ��������
                }
                bookingToCancel->cancelBooking(); // ������ ������ ������������
                cout << "������������ ID " << id << " ��������.\n";
            } else {
                cout << "������������ � ID " << id << " �� ������� ��� �� �������� ��������.\n";
            }
            break;
        }
        case 0:
            saveToFile<Booking>("Booking.txt", bookings);
            saveToFile<Room>("Room.txt", rooms); // ������ ������ ��� ����������
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments, const vector<Room>& rooms) {
    int choice;
    do {
        cout << "\n==== ���� ������ ====\n";
        cout << "1. �������� ������ �� ������������\n";
        cout << "2. �������� ��� ��������� �� ������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            cout << "�������� ������������ ��� ������:\n";
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() == "�������") { // ���������� ����� ������ ��������
                     // ��� ����������� ������� ����� ������������� ������ guests
                    cout << "ID ������������: " << b.getID() 
                              << ", ����� �������: " << b.getRoomNumber() 
                              //<< ", ����� ID: " << b.getGuestId() // ���� ����� ������ ����������
                              << endl;
                    activeBookingExists = true;
                }
            }
            if (!activeBookingExists) {
                cout << "��� �������� ������������ ��� ������.\n";
                break;
            }

            cout << "������� ID ������������ ��� ������: ";
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
                    cout << "��������������� ��������� ����������: " << cost << " ���." << endl;
                } else {
                    cout << "������: �� ������� ����� ������� ��� ������� ���������." << endl;
                    // ����� ���������� ������ ����� ������� ��� �������� ��������
                }


                cout << "������� ����� ������: ";
                double amount;
                while (!(cin >> amount) || amount <= 0) {
                    cout << "�������� �����. ������� ������������� �����: ";
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                }
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');


                string method = getStringInput("������� ������ ������ (��������, �����): ");
                string date = getStringInput("������� ���� ������ (��.��.����): ");

                Payment newPayment(*bookingToPay, amount, method, date);
                newPayment.processPayment(); // ����� ���������� �� ���������
                payments.push_back(newPayment);
                
                bookingToPay->completeBooking(); // ������ ������ ������������ �� "���������"
                // ������ ������� (isAvailable) �� ������, �.�. ��� ����� ���� ������������� ��������� ������.
                // ������������ ������� ������ ����������� ��� ������ (��� ������).
                // ���� "���������" ��������, ��� ����� ������, �� ������� ����� ����������.
                // Room* roomToUpdate = findRoomByNumber(rooms, bookingToPay->getRoomNumber());
                // if(roomToUpdate) roomToUpdate->updateStatus(true);


                cout << "������ ���������. ������ ������������ ID " << bookingId << " ������� �� '���������'.\n";
            } else {
                cout << "������������ � ID " << bookingId << " �� ������� ��� �� �������� �������� ��� ������.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                cout << "��������� �� ������ ���.\n";
                break;
            }
            cout << "��� ��������� �� ������:\n";
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
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void employeeMenu(vector<Employee>& employees) {
    // � ������������ ���� ��� ���� ������ �������� ������ � ������.
    // ������� ��� ����� ��������������, ���� �����������.
    // ���� ��� ������� ��� ���� ��� ������������.
    // TODO: ����������� ����������� ���� ��� ����������� (����������, ��������, ��������������)
    int choice;
     do {
        cout << "\n==== ���� ����������� ====\n";
        cout << "1. �������� ���� �����������\n";
        cout << "2. �������� ������ ����������\n";
        // �������� ������ �����: �������, �������������...
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (employees.empty()) {
                cout << "������ ����������� ����.\n";
            } else {
                cout << "������ �����������:\n";
                for (const auto& e : employees) {
                    e.displayInfo();
                }
            }
            break;
        case 2: {
            string name = getStringInput("������� ��� ����������: ");
            string phone = getStringInput("�������: ");
            string email = getStringInput("Email: ");
            string position = getStringInput("���������: ");

            Employee newEmployee(Employee::employeeCounter, name, phone, email, position);
            employees.push_back(newEmployee);
            Employee::employeeCounter++;
            cout << "��������� ��������. ID: " << newEmployee.getId() << endl;
            break;
        }
        case 0:
            saveToFile<Employee>("Employee.txt", employees);
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
    
}