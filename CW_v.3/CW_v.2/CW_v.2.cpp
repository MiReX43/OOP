#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <memory>
#include <windows.h>

using namespace std;

int guestCounter = 1;
int bookingCounter = 1;
int paymentCounter = 1;
int employeeCounter = 1;

// ---------------- ����������� ����� Person ----------------
class Person {
protected:
    int id;
    string name;
    string phone;
    string email;

public:
    Person(int id, string name, string phone, string email)
        : id(id), name(name), phone(phone), email(email) {
    }

    virtual void displayInfo() const = 0; // ����� ����������� �����

    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
};

// ---------------- ����� Guest ----------------
class Guest : public Person {
    string passportData;

public:
    Guest(int i, string name, string phone, string email, string passportData)
        : Person(i, name, phone, email), passportData(passportData) {
        if (i >= guestCounter) guestCounter = i + 1;
    }

    void updateContactInfo(string newPhone, string newEmail) {
        phone = newPhone;
        email = newEmail;
    }

    void displayInfo() const override {
        cout << "ID: " << id
            << ", ���: " << name
            << ", �������: " << phone
            << ", Email: " << email
            << endl;
    }

    string toString() const {
        return to_string(id) + "," + name + "," + phone + "," + email + "," + passportData;
    }

    static Guest fromString(const string& line) {
        stringstream ss(line);
        string idStr, name, phone, email, passport;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, passport, ',');
        int id = stoi(idStr);
        return Guest(id, name, phone, email, passport);
    }
};

// ---------------- ����� RoomCategory ----------------
class RoomCategory {
    int id;
    string name;
    string description;
    vector<string> services;

public:
    RoomCategory(int i, string name, string description, vector<string> services)
        : id(i), name(name), description(description), services(services) {
        if (i >= categoryCounter) categoryCounter = i + 1;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getDescription() const { return description; }

    void getServices() const {
        if (services.empty()) {
            cout << "  (��� �����)" << endl;
        }
        else {
            for (size_t i = 0; i < services.size(); ++i) {
                cout << "  " << (i + 1) << ". " << services[i] << endl;
            }
        }
    }

    void setServices(const vector<string>& newServices) {
        services = newServices;
    }

    string toString() const {
        string result = to_string(id) + "," + name + "," + description + ",";
        for (size_t i = 0; i < services.size(); ++i) {
            result += services[i];
            if (i != services.size() - 1)
                result += ";";
        }
        return result;
    }

    static RoomCategory fromString(const string& line) {
        stringstream ss(line);
        string idStr, name, description, servicesStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, description, ',');
        getline(ss, servicesStr);
        int id = stoi(idStr);
        vector<string> servs;
        stringstream servStream(servicesStr);
        string service;
        while (getline(servStream, service, ';')) {
            if (!service.empty()) servs.push_back(service);
        }
        return RoomCategory(id, name, description, servs);
    }

    static int categoryCounter;
};
int RoomCategory::categoryCounter = 1;

// ---------------- ����� Room ----------------
class Room {
    int roomNumber;
    int categoryId;
    int capacity;
    bool isAvailable;
    double pricePerNight;

public:
    Room(int number, int catId, int cap, bool avail, double price)
        : roomNumber(number), categoryId(catId), capacity(cap), isAvailable(avail), pricePerNight(price) {
        if (number >= roomCounter) roomCounter = number + 1;
    }

    int getRoomNumber() const { return roomNumber; }
    int getCategoryId() const { return categoryId; }
    bool getAvailability() const { return isAvailable; }
    void updateStatus(bool status) { isAvailable = status; }
    double getPrice() const { return pricePerNight; }

    void displayDetails(const RoomCategory& category) const {
        cout << "����� #: " << roomNumber
            << ", ���������: " << category.getName()
            << ", ���-�� ����: " << capacity
            << ", ��������: " << (isAvailable ? "��" : "���")
			<< ", ����: " << pricePerNight << " ���./����"
            << endl;
    }

    string toString() const {
        return to_string(roomNumber) + "," + to_string(categoryId) + "," + to_string(capacity)
            + "," + (isAvailable ? "1" : "0") + "," + to_string(pricePerNight);
    }

    static Room fromString(const string& line) {
        stringstream ss(line);
        string roomNumStr, catIdStr, capStr, availStr, priceStr;
        getline(ss, roomNumStr, ',');
        getline(ss, catIdStr, ',');
        getline(ss, capStr, ',');
        getline(ss, availStr, ',');
        getline(ss, priceStr, ',');
        int roomNum = stoi(roomNumStr);
        int catId = stoi(catIdStr);
        int cap = stoi(capStr);
        bool avail = (availStr == "1");
        double price = stod(priceStr);
        return Room(roomNum, catId, cap, avail, price);
    }

    static int roomCounter;
};
int Room::roomCounter = 1;

// ---------------- ����� Employee ----------------
class Employee : public Person {
    string position;

public:
    Employee(int id, string name, string phone, string email, string pos)
        : Person(id, name, phone, email), position(pos) {
        if (id >= employeeCounter) employeeCounter = id + 1;
    }

    void displayInfo() const override {
        cout << "���: " << name << ", ���������: " << position << endl;
    }

    string toString() const {
        return to_string(id) + "," + name + "," + phone + "," + email + "," + position;
    }

    static Employee fromString(const string& line) {
        stringstream ss(line);
        string idStr, name, phone, email, pos;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, pos, ',');
        int id = stoi(idStr);
        return Employee(id, name, phone, email, pos);
    }
};

// ---------------- ����� Booking ----------------
class Booking {
    int bookingID;
    int guestId;
    int roomNumber;
    string checkInDate;
    string checkOutDate;
    string status;

public:
    Booking(int id, int gid, int rn, string in, string out, string st)
        : bookingID(id), guestId(gid), roomNumber(rn), checkInDate(in), checkOutDate(out), status(st) {
        if (id >= bookingCounter) bookingCounter = id + 1;
    }

    Booking(Guest g, Room r, string in, string out)
        : bookingID(bookingCounter++), guestId(g.getId()), roomNumber(r.getRoomNumber()),
        checkInDate(in), checkOutDate(out), status("�������") {
    }

    int getID() const { return bookingID; }
    int getGuestId() const { return guestId; }
    int getRoomNumber() const { return roomNumber; }
    string getStatus() const { return status; }

    void confirmBooking() { status = "�������"; }
    void cancelBooking() { status = "��������"; }
    void completBooking() { status = "���������"; }

    double calculateCost(double pricePerNight) const {
        return 3.0 * pricePerNight; // ������������� ���������� �����
    }

    void display(const Guest& guest, const Room& room) const {
        cout << "ID ������������: " << bookingID
            << ", �����: " << guest.getName()
            << ", ����� #: " << room.getRoomNumber()
            << ", ��: " << checkInDate
            << " ��: " << checkOutDate
            << ", ������: " << status
            << endl;
    }

    string toString() const {
        return to_string(bookingID) + "," + to_string(guestId) + "," + to_string(roomNumber) + "," + checkInDate + "," + checkOutDate + "," + status;
    }

    static Booking fromString(const string& line) {
        stringstream ss(line);
        string bidStr, gidStr, rnStr, inDate, outDate, st;
        getline(ss, bidStr, ',');
        getline(ss, gidStr, ',');
        getline(ss, rnStr, ',');
        getline(ss, inDate, ',');
        getline(ss, outDate, ',');
        getline(ss, st);
        int bid = stoi(bidStr);
        int gid = stoi(gidStr);
        int rn = stoi(rnStr);
        return Booking(bid, gid, rn, inDate, outDate, st);
    }
};

// ---------------- ����� Payment ----------------
class Payment {
    int paymentID;
    int bookingID;
    double amount;
    string paymentDate;
    string paymentMethod;

public:
    Payment(int pid, int bid, double amt, string method, string date)
        : paymentID(pid), bookingID(bid), amount(amt), paymentMethod(method), paymentDate(date) {
        if (pid >= paymentCounter) paymentCounter = pid + 1;
    }

    Payment(Booking b, double amt, string method, string date)
        : paymentID(paymentCounter++), bookingID(b.getID()), amount(amt), paymentMethod(method), paymentDate(date) {
    }

    void processPayment() {
        cout << "��������� ������� � ������� " << amount << " ���. ��������� " << paymentMethod << endl;
    }

    void printReceipt() const {
        cout << "ID ���������: " << paymentID
            << ", ID ������������: " << bookingID
			<< ", �����: " << amount << " ���."
            << ", ����: " << paymentDate
            << ", ������ ������: " << paymentMethod
            << endl;
    }

    string toString() const {
        return to_string(paymentID) + "," + to_string(bookingID) + "," + to_string(amount) + "," + paymentMethod + "," + paymentDate;
    }

    static Payment fromString(const string& line) {
        stringstream ss(line);
        string pidStr, bidStr, amtStr, method, date;
        getline(ss, pidStr, ',');
        getline(ss, bidStr, ',');
        getline(ss, amtStr, ',');
        getline(ss, method, ',');
        getline(ss, date, ',');
        int pid = stoi(pidStr);
        int bid = stoi(bidStr);
        double amt = stod(amtStr);
        return Payment(pid, bid, amt, method, date);
    }
};

// --- ������� ������/������ ������ ---

template <typename T>
void saveToFile(const string& filename, const vector<T>& vec) {
    ofstream fout(filename);
    for (const auto& item : vec) {
        fout << item.toString() << "\n";
    }
    fout.close();
}

template <typename T>
void loadFromFile(const string& filename, vector<T>& vec) {
    ifstream fin(filename);
    string line;
    vec.clear();
    while (getline(fin, line)) {
        if (line.empty()) continue;
        vec.push_back(T::fromString(line));
    }
    fin.close();
}

// ----------------- ���������� ������� � ���� -----------------

void showMainMenu();
void guestMenu(vector<Guest>& guests);
void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories);
void categoryMenu(vector<RoomCategory>& categories);
void editServicesMenu(vector<RoomCategory>& categories);
void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories);
void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments);
void employeeMenu(vector<Employee>& employees);
RoomCategory* findCategoryById(vector<RoomCategory>& categories, int id);
Room* findRoomByNumber(vector<Room>& rooms, int number);
Guest* findGuestById(vector<Guest>& guests, int id);
Booking* findBookingById(vector<Booking>& bookings, int id);

void loadAllData(vector<Guest>& guests, vector<RoomCategory>& categories, vector<Room>& rooms,
    vector<Employee>& employees, vector<Booking>& bookings, vector<Payment>& payments) {
    loadFromFile<Guest>("Guest.txt", guests);
    loadFromFile<RoomCategory>("RoomCategory.txt", categories);
    loadFromFile<Room>("Room.txt", rooms);
    loadFromFile<Employee>("Employee.txt", employees);
    loadFromFile<Booking>("Booking.txt", bookings);
    loadFromFile<Payment>("Payment.txt", payments);
}

void saveAllData(vector<Guest>& guests, vector<RoomCategory>& categories, vector<Room>& rooms,
    vector<Employee>& employees, vector<Booking>& bookings, vector<Payment>& payments) {
    saveToFile<Guest>("Guest.txt", guests);
    saveToFile<RoomCategory>("RoomCategory.txt", categories);
    saveToFile<Room>("Room.txt", rooms);
    saveToFile<Employee>("Employee.txt", employees);
    saveToFile<Booking>("Booking.txt", bookings);
    saveToFile<Payment>("Payment.txt", payments);
}

// ����� ��������� �� id
RoomCategory* findCategoryById(vector<RoomCategory>& categories, int id) {
    for (auto& cat : categories) {
        if (cat.getId() == id)
            return &cat;
    }
    return nullptr;
}

// ����� ������� �� ������
Room* findRoomByNumber(vector<Room>& rooms, int number) {
    for (auto& r : rooms) {
        if (r.getRoomNumber() == number)
            return &r;
    }
    return nullptr;
}

// ����� ����� �� ID
Guest* findGuestById(vector<Guest>& guests, int id) {
    for (auto& g : guests) {
        if (g.getId() == id)
            return &g;
    }
    return nullptr;
}

// ����� ������������ �� ID
Booking* findBookingById(vector<Booking>& bookings, int id) {
    for (auto& b : bookings) {
        if (b.getID() == id)
            return &b;
    }
    return nullptr;
}

int main() {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    vector<Guest> guests;
    vector<RoomCategory> categories;
    vector<Room> rooms;
    vector<Employee> employees;
    vector<Booking> bookings;
    vector<Payment> payments;

    loadAllData(guests, categories, rooms, employees, bookings, payments);

    // ���� ��� ��������� - �������������� �������� (����� ���� ��� �������������)
    if (categories.empty()) {
        categories.push_back(RoomCategory(1, "Standard", "����������� �����", { "WiFi", "�����������" }));
        categories.push_back(RoomCategory(2, "Deluxe", "����� ���������� ������������", { "WiFi", "�����������", "����������" }));
        categories.push_back(RoomCategory(3, "Suite", "����", { "WiFi", "�����������", "����������", "�������" }));
    }

    if (employees.empty()) {
        employees.push_back(Employee(1, "������� �.�", "1234567890", "manager@example.com", "��������"));
    }

    // ���� ��� ������ - ������� ���������
    if (rooms.empty()) {
        rooms.push_back(Room(101, categories[0].getId(), 2, true, 50));
        rooms.push_back(Room(102, categories[1].getId(), 3, true, 80));
        rooms.push_back(Room(201, categories[2].getId(), 4, true, 150));
    }

    int choice;
    do {
        showMainMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            guestMenu(guests);
            saveToFile<Guest>("Guest.txt", guests);
            break;
        case 2:
            roomMenu(rooms, categories);
            saveToFile<Room>("Room.txt", rooms);
            saveToFile<RoomCategory>("RoomCategory.txt", categories);
            break;
        case 3:
            bookingMenu(guests, rooms, bookings, categories);
            saveToFile<Booking>("Booking.txt", bookings);
            saveToFile<Room>("Room.txt", rooms);
            break;
        case 4:
            paymentMenu(bookings, payments);
            saveToFile<Payment>("Payment.txt", payments);
            break;
        case 5:
            employeeMenu(employees);
            saveToFile<Employee>("Employee.txt", employees);
            break;
        case 0:
            cout << "����� �� ���������..." << endl;
            saveAllData(guests, categories, rooms, employees, bookings, payments);
            break;
        default:
            cout << "�������� �����. ��������� �������." << endl;
        }
    } while (choice != 0);

    return 0;
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
        cin >> choice;

        switch (choice) {
        case 1: {
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
            for (const auto& g : guests) {
                g.displayInfo();
            }
            cout << "������� ID ��� ���������: ";
            int id; cin >> id;
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                string phone, email;
                cout << "������� ����� �������: "; cin.ignore(); getline(cin, phone);
                cout << "������� ����� email: "; getline(cin, email);
                guest->updateContactInfo(phone, email);
                cout << "���������� ���������� ���������.\n";
            }
            else {
                cout << "�������� ID.\n";
            }
            break;
        }
        case 0:
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
        cout << "1. �������� ������\n";
        cout << "2. �������� ������ ������\n";
        cout << "3. ��������� �������\n";
        cout << "4. �������� ������ �����\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)" << endl;
            }
            break;
        case 2: {
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)" << endl;
            }
            int number;
            cout << "������� ����� �������: ";
            cin >> number;
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                cout << "������� ����� ������ (1 - ��������, 0 - �����): ";
                int avail;
                cin >> avail;
                room->updateStatus(avail != 0);
                cout << "������ ��������.\n";
            }
            else {
                cout << "������� �� �������.\n";
            }
            break;
        }
        case 3:
            categoryMenu(categories);
            break;
        case 4:
            editServicesMenu(categories);
            break;
        case 0:
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void categoryMenu(vector<RoomCategory>& categories) {
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
        c.getServices();
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
    int id; cin >> id;
    RoomCategory* category = findCategoryById(categories, id);
    if (!category) {
        cout << "�������� ID ���������.\n";
        return;
    }
    cin.ignore();
    cout << "������� ������:\n";
    category->getServices();
    cout << "������� ����� ������ ����� ������� (��������: WiFi,�������,�������): ";
    string line;
    getline(cin, line);
    vector<string> newServices;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        if (!token.empty()) {
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != string::npos && end != string::npos)
                newServices.push_back(token.substr(start, end - start + 1));
            else if (start != string::npos)
                newServices.push_back(token.substr(start));
        }
    }
    category->setServices(newServices);
    cout << "������ ����� ��������.\n";
}

void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== ���� ������������ ====\n";
        cout << "1. ����������� � ������������\n";
        cout << "2. ������� ������������\n";
        cout << "3. �������� ������������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1: {

            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                }
                else {
                    cout << "������: �� ������� ����� ����� ��� ������� ��� ������������ ID: " << b.getID() << endl;
                }
            }
            break;
        }
        case 2: {
            string name, phone, email, passport, checkIn, checkOut;
            cout << "������� ��� �����: "; cin.ignore(); getline(cin, name);
            cout << "�������: "; getline(cin, phone);
            cout << "Email: "; getline(cin, email);
            cout << "���������� ������: "; getline(cin, passport);
            Guest g(guestCounter++, name, phone, email, passport);
            guests.push_back(g);

            if (rooms.empty()) {
                cout << "��� ��������� ������.\n";
                break;
            }
            cout << "��������� ������:\n";
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat)
                        r.displayDetails(*cat);
                    else
                        cout << "Room #: " << r.getRoomNumber() << " (��������� �� �������)" << endl;
                }
            }
            int number;
            cout << "�������� ����� �������: "; cin >> number;
            Room* selectedRoom = findRoomByNumber(rooms, number);
            if (!selectedRoom || !selectedRoom->getAvailability()) {
                cout << "������� ����������.\n";
                break;
            }
            cout << "���� ������: "; cin.ignore(); getline(cin, checkIn);
            cout << "���� ������: "; getline(cin, checkOut);
            Booking b(g, *selectedRoom, checkIn, checkOut);
            b.confirmBooking();
            selectedRoom->updateStatus(false);
            bookings.push_back(b);
            cout << "������������ �������.\n";
            break;
        }
        case 3: {
            if (bookings.empty()) {
                cout << "������������ ���.\n";
                break;
            }
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                }
                else {
                    cout << "������: �� ������� ����� ����� ��� ������� ��� ������������ ID: " << b.getID() << endl;
                }
            }
            cout << "�������� ID ��� ������: ";
            int id; cin >> id;
            Booking* booking = findBookingById(bookings, id);
            if (booking) {
                booking->cancelBooking();
                Room* room = findRoomByNumber(rooms, booking->getRoomNumber());
                if (room)
                    room->updateStatus(true);
                cout << "������������ ��������.\n";
            }
            else {
                cout << "�������� ID.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments) {
    int choice;
    do {
        cout << "\n==== ���� ������ ====\n";
        cout << "1. �������� ������\n";
        cout << "2. �������� ��������� �� ������\n";
        cout << "0. ����� � ������� ����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() != "��������" && b.getStatus() != "���������") {
                    activeBookingExists = true;
                    break;
                }
            }
            if (!activeBookingExists) {
                cout << "��� ������������ ��� ������.\n";
                break;
            }

            for (const auto& b : bookings) {
                if (b.getStatus() == "�������") {
                    cout << "ID: " << b.getID() << ", ����� #: " << b.getRoomNumber() << endl;
                }
            }

            cout << "�������� ID ������������: ";
            int id; cin >> id;
            Booking* booking = findBookingById(bookings, id);

            if (booking && booking->getStatus() == "�������") {
                double price = 0; // ����� ����� �������� ������ ��� ������� ���������
                cout << "������� ����� ������: ";
                double amount; cin >> amount;
                cin.ignore();
                string method, date;
                cout << "������� ������ ������: "; getline(cin, method);
                cout << "������� ���� ������: "; getline(cin, date);

                Payment p(*booking, amount, method, date);
                p.processPayment();
                payments.push_back(p);

                booking->completBooking(); // ������������� ������ "���������"
                cout << "������ ���������. ������ ������������ ������� �� '���������'.\n";
            }
            else {
                cout << "�������� ID ��� ������������ �� �������.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                cout << "��������� ���.\n";
                break;
            }
            for (const auto& p : payments) {
                p.printReceipt();
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);
}

void employeeMenu(vector<Employee>& employees) {

    if (employees.empty()) {
        cout << "������ ����������� ����.\n";
    }
    else {
        for (const auto& e : employees) {
            e.displayInfo();
        }
    }
    cout << "�������� �����. ���������� �����.\n";
}