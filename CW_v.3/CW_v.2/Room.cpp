#include "Room.h"
#include <iostream> // Для cout
#include <iomanip>  // Для std::fixed, std::setprecision (если нужно форматировать цену)


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
    std::cout << "Номер #: " << roomNumber
        << ", Категория: " << category.getName()
        << ", Кол-во мест: " << capacity
        << ", Доступен: " << (isAvailable ? "Да" : "Нет")
        << ", Цена: " << std::fixed << std::setprecision(2) << pricePerNight << " руб./ночь"
        << std::endl;
}

std::string Room::toString() const {
    // Используем std::ostringstream для корректного преобразования double в строку
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << pricePerNight;

    return std::to_string(roomNumber) + "," + std::to_string(categoryId) + "," + std::to_string(capacity)
        + "," + (isAvailable ? "1" : "0") + "," + oss.str();
}

Room Room::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string roomNumStr, catIdStr, capStr, availStr, priceStr;
    std::getline(ss, roomNumStr, ',');
    std::getline(ss, catIdStr, ',');
    std::getline(ss, capStr, ',');
    std::getline(ss, availStr, ',');
    std::getline(ss, priceStr, ',');

    int roomNum = 0;
    if (!roomNumStr.empty()) roomNum = std::stoi(roomNumStr);
    int catId = 0;
    if (!catIdStr.empty()) catId = std::stoi(catIdStr);
    int cap = 0;
    if (!capStr.empty()) cap = std::stoi(capStr);
    bool avail = (availStr == "1");
    double price = 0.0;
    if (!priceStr.empty()) price = std::stod(priceStr);

    return Room(roomNum, catId, cap, avail, price);
}