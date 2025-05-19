#include "Room.h"
#include <iostream> // Для cout
#include <iomanip>  // Для fixed, setprecision (если нужно форматировать цену)

using namespace std;
int Room::roomCounter = 1; // Инициализация

Room::Room(int number, int catId, int cap, bool avail, double price)
    : roomNumber(number), categoryId(catId), capacity(cap), isAvailable(avail), pricePerNight(price) {
    if (number >= roomCounter) roomCounter = number + 1; // Логика счетчика может быть разной, если номера не всегда последовательны
}

int Room::getRoomNumber() const { return roomNumber; }
int Room::getCategoryId() const { return categoryId; }
int Room::getCapacity() const { return capacity; }
bool Room::getAvailability() const { return isAvailable; }
void Room::updateStatus(bool status) { isAvailable = status; }
double Room::getPrice() const { return pricePerNight; }

void Room::displayDetails(const RoomCategory& category) const {
    cout << "Номер #: " << roomNumber
        << ", Категория: " << category.getName()
        << ", Кол-во мест: " << capacity
        << ", Доступен: " << (isAvailable ? "Да" : "Нет")
        << ", Цена: " << fixed << setprecision(2) << pricePerNight << " руб./ночь"
        << endl;
}

string Room::toString() const {
    // Используем ostringstream для корректного преобразования double в строку
    ostringstream oss;
    oss << fixed << setprecision(2) << pricePerNight;

    return to_string(roomNumber) + "," + to_string(categoryId) + "," + to_string(capacity)
        + "," + (isAvailable ? "1" : "0") + "," + oss.str();
}

Room Room::fromString(const string& line) {
    stringstream ss(line);
    string roomNumStr, catIdStr, capStr, availStr, priceStr;
    getline(ss, roomNumStr, ',');
    getline(ss, catIdStr, ',');
    getline(ss, capStr, ',');
    getline(ss, availStr, ',');
    getline(ss, priceStr, ',');

    int roomNum = 0;
    if (!roomNumStr.empty()) roomNum = stoi(roomNumStr);
    int catId = 0;
    if (!catIdStr.empty()) catId = stoi(catIdStr);
    int cap = 0;
    if (!capStr.empty()) cap = stoi(capStr);
    bool avail = (availStr == "1");
    double price = 0.0;
    if (!priceStr.empty()) price = stod(priceStr);

    return Room(roomNum, catId, cap, avail, price);
}