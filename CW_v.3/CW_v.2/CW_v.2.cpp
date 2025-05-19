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

// ---------------- Абстрактный класс Person ----------------
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

    virtual void displayInfo() const = 0; // Чисто виртуальный метод

    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
};

// ---------------- Класс Guest ----------------
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
            << ", ФИО: " << name
            << ", Телефон: " << phone
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

// ---------------- Класс RoomCategory ----------------
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
            cout << "  (нет услуг)" << endl;
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

// ---------------- Класс Room ----------------
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
        cout << "Номер #: " << roomNumber
            << ", Категория: " << category.getName()
            << ", Кол-во мест: " << capacity
            << ", Доступен: " << (isAvailable ? "Да" : "Нет")
			<< ", Цена: " << pricePerNight << " руб./ночь"
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

// ---------------- Класс Employee ----------------
class Employee : public Person {
    string position;

public:
    Employee(int id, string name, string phone, string email, string pos)
        : Person(id, name, phone, email), position(pos) {
        if (id >= employeeCounter) employeeCounter = id + 1;
    }

    void displayInfo() const override {
        cout << "Имя: " << name << ", Должность: " << position << endl;
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

// ---------------- Класс Booking ----------------
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
        checkInDate(in), checkOutDate(out), status("Активно") {
    }

    int getID() const { return bookingID; }
    int getGuestId() const { return guestId; }
    int getRoomNumber() const { return roomNumber; }
    string getStatus() const { return status; }

    void confirmBooking() { status = "Активно"; }
    void cancelBooking() { status = "Отменено"; }
    void completBooking() { status = "Завершено"; }

    double calculateCost(double pricePerNight) const {
        return 3.0 * pricePerNight; // фиксированное количество ночей
    }

    void display(const Guest& guest, const Room& room) const {
        cout << "ID бронирования: " << bookingID
            << ", Гость: " << guest.getName()
            << ", Номер #: " << room.getRoomNumber()
            << ", От: " << checkInDate
            << " До: " << checkOutDate
            << ", Статус: " << status
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

// ---------------- Класс Payment ----------------
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
        cout << "Обработка платежа в размере " << amount << " руб. используя " << paymentMethod << endl;
    }

    void printReceipt() const {
        cout << "ID Квитанции: " << paymentID
            << ", ID бронирования: " << bookingID
			<< ", Сумма: " << amount << " руб."
            << ", Дата: " << paymentDate
            << ", Способ оплаты: " << paymentMethod
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

// --- Функции чтения/записи данных ---

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

// ----------------- Глобальные функции и меню -----------------

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

// Найти категорию по id
RoomCategory* findCategoryById(vector<RoomCategory>& categories, int id) {
    for (auto& cat : categories) {
        if (cat.getId() == id)
            return &cat;
    }
    return nullptr;
}

// Найти комнату по номеру
Room* findRoomByNumber(vector<Room>& rooms, int number) {
    for (auto& r : rooms) {
        if (r.getRoomNumber() == number)
            return &r;
    }
    return nullptr;
}

// Найти гостя по ID
Guest* findGuestById(vector<Guest>& guests, int id) {
    for (auto& g : guests) {
        if (g.getId() == id)
            return &g;
    }
    return nullptr;
}

// Найти бронирование по ID
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

    // Если нет категорий - инициализируем примером (чтобы было что редактировать)
    if (categories.empty()) {
        categories.push_back(RoomCategory(1, "Standard", "Стандартный номер", { "WiFi", "Холодильник" }));
        categories.push_back(RoomCategory(2, "Deluxe", "Номер повышенной комфортности", { "WiFi", "Холодильник", "Кофемашина" }));
        categories.push_back(RoomCategory(3, "Suite", "Люкс", { "WiFi", "Холодильник", "Кофемашина", "Минибар" }));
    }

    if (employees.empty()) {
        employees.push_back(Employee(1, "Гиревой Д.И", "1234567890", "manager@example.com", "Менеджер"));
    }

    // Если нет комнат - добавим примерные
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
            cout << "Выход из программы..." << endl;
            saveAllData(guests, categories, rooms, employees, bookings, payments);
            break;
        default:
            cout << "Неверный выбор. Повторите попытку." << endl;
        }
    } while (choice != 0);

    return 0;
}

void showMainMenu() {
    cout << "\n==== Главное меню ====\n";
    cout << "1. Гости\n";
    cout << "2. Номера\n";
    cout << "3. Бронирование\n";
    cout << "4. Оплата\n";
    cout << "5. Сотрудники\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

void guestMenu(vector<Guest>& guests) {
    int choice;
    do {
        cout << "\n==== Меню гостей ====\n";
        cout << "1. Вывести информацию о гостях\n";
        cout << "2. Изменить контактную информацию\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
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
                cout << "Список гостей пуст.\n";
                break;
            }
            for (const auto& g : guests) {
                g.displayInfo();
            }
            cout << "Введите ID для изменения: ";
            int id; cin >> id;
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                string phone, email;
                cout << "Введите новый телефон: "; cin.ignore(); getline(cin, phone);
                cout << "Введите новый email: "; getline(cin, email);
                guest->updateContactInfo(phone, email);
                cout << "Контактная информация обновлена.\n";
            }
            else {
                cout << "Неверный ID.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== Меню номеров ====\n";
        cout << "1. Показать номера\n";
        cout << "2. Изменить статус номера\n";
        cout << "3. Категории номеров\n";
        cout << "4. Изменить список услуг\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)" << endl;
            }
            break;
        case 2: {
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)" << endl;
            }
            int number;
            cout << "Введите номер комнаты: ";
            cin >> number;
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                cout << "Введите новый статус (1 - доступен, 0 - занят): ";
                int avail;
                cin >> avail;
                room->updateStatus(avail != 0);
                cout << "Статус обновлен.\n";
            }
            else {
                cout << "Комната не найдена.\n";
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
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void categoryMenu(vector<RoomCategory>& categories) {
    cout << "\n==== Категории номеров ====\n";
    if (categories.empty()) {
        cout << "Нет категорий номеров.\n";
        return;
    }
    for (const auto& c : categories) {
        cout << "ID: " << c.getId()
            << ", Название: " << c.getName()
            << ", Описание: " << c.getDescription()
            << endl;
        cout << "  Услуги:\n";
        c.getServices();
    }
}

void editServicesMenu(vector<RoomCategory>& categories) {
    if (categories.empty()) {
        cout << "Нет категорий для редактирования.\n";
        return;
    }
    cout << "\n==== Изменить список услуг ====\n";
    cout << "Список категорий:\n";
    for (const auto& c : categories) {
        cout << "ID: " << c.getId() << ", Название: " << c.getName() << endl;
    }
    cout << "Введите ID категории для изменения услуг: ";
    int id; cin >> id;
    RoomCategory* category = findCategoryById(categories, id);
    if (!category) {
        cout << "Неверный ID категории.\n";
        return;
    }
    cin.ignore();
    cout << "Текущие услуги:\n";
    category->getServices();
    cout << "Введите новые услуги через запятую (например: WiFi,Минибар,Завтрак): ";
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
    cout << "Список услуг обновлен.\n";
}

void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== Меню бронирования ====\n";
        cout << "1. Иноформация о бронировании\n";
        cout << "2. Создать бронирование\n";
        cout << "3. Отменить бронирование\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
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
                    cout << "Ошибка: не удалось найти гостя или комнату для бронирования ID: " << b.getID() << endl;
                }
            }
            break;
        }
        case 2: {
            string name, phone, email, passport, checkIn, checkOut;
            cout << "Введите имя гостя: "; cin.ignore(); getline(cin, name);
            cout << "Телефон: "; getline(cin, phone);
            cout << "Email: "; getline(cin, email);
            cout << "Паспортные данные: "; getline(cin, passport);
            Guest g(guestCounter++, name, phone, email, passport);
            guests.push_back(g);

            if (rooms.empty()) {
                cout << "Нет доступных комнат.\n";
                break;
            }
            cout << "Доступные номера:\n";
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat)
                        r.displayDetails(*cat);
                    else
                        cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)" << endl;
                }
            }
            int number;
            cout << "Выберите номер комнаты: "; cin >> number;
            Room* selectedRoom = findRoomByNumber(rooms, number);
            if (!selectedRoom || !selectedRoom->getAvailability()) {
                cout << "Комната недоступна.\n";
                break;
            }
            cout << "Дата въезда: "; cin.ignore(); getline(cin, checkIn);
            cout << "Дата выезда: "; getline(cin, checkOut);
            Booking b(g, *selectedRoom, checkIn, checkOut);
            b.confirmBooking();
            selectedRoom->updateStatus(false);
            bookings.push_back(b);
            cout << "Бронирование создано.\n";
            break;
        }
        case 3: {
            if (bookings.empty()) {
                cout << "Бронирований нет.\n";
                break;
            }
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                }
                else {
                    cout << "Ошибка: не удалось найти гостя или комнату для бронирования ID: " << b.getID() << endl;
                }
            }
            cout << "Выберите ID для отмены: ";
            int id; cin >> id;
            Booking* booking = findBookingById(bookings, id);
            if (booking) {
                booking->cancelBooking();
                Room* room = findRoomByNumber(rooms, booking->getRoomNumber());
                if (room)
                    room->updateStatus(true);
                cout << "Бронирование отменено.\n";
            }
            else {
                cout << "Неверный ID.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments) {
    int choice;
    do {
        cout << "\n==== Меню оплаты ====\n";
        cout << "1. Провести оплату\n";
        cout << "2. Показать квитанции об оплате\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() != "Отменено" && b.getStatus() != "Завершено") {
                    activeBookingExists = true;
                    break;
                }
            }
            if (!activeBookingExists) {
                cout << "Нет бронирований для оплаты.\n";
                break;
            }

            for (const auto& b : bookings) {
                if (b.getStatus() == "Активно") {
                    cout << "ID: " << b.getID() << ", Номер #: " << b.getRoomNumber() << endl;
                }
            }

            cout << "Выберите ID бронирования: ";
            int id; cin >> id;
            Booking* booking = findBookingById(bookings, id);

            if (booking && booking->getStatus() == "Активно") {
                double price = 0; // Здесь можно добавить логику для расчета стоимости
                cout << "Введите сумму оплаты: ";
                double amount; cin >> amount;
                cin.ignore();
                string method, date;
                cout << "Введите способ оплаты: "; getline(cin, method);
                cout << "Введите дату оплаты: "; getline(cin, date);

                Payment p(*booking, amount, method, date);
                p.processPayment();
                payments.push_back(p);

                booking->completBooking(); // Устанавливаем статус "Завершено"
                cout << "Оплата проведена. Статус бронирования изменен на 'Завершено'.\n";
            }
            else {
                cout << "Неверный ID или бронирование не активно.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                cout << "Квитанций нет.\n";
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
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void employeeMenu(vector<Employee>& employees) {

    if (employees.empty()) {
        cout << "Список сотрудников пуст.\n";
    }
    else {
        for (const auto& e : employees) {
            e.displayInfo();
        }
    }
    cout << "Неверный выбор. Попробуйте снова.\n";
}