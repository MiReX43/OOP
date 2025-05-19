#include "RoomCategory.h"


int RoomCategory::categoryCounter = 1; // Инициализация

RoomCategory::RoomCategory(int i, std::string name, std::string description, std::vector<std::string> services)
    : id(i), name(std::move(name)), description(std::move(description)), services(std::move(services)) {
    if (i >= categoryCounter) categoryCounter = i + 1;
}

int RoomCategory::getId() const { return id; }
std::string RoomCategory::getName() const { return name; }
std::string RoomCategory::getDescription() const { return description; }

const std::vector<std::string>& RoomCategory::getServicesList() const {
    return services;
}

void RoomCategory::printServices() const {
    if (services.empty()) {
        std::cout << "  (нет услуг)" << std::endl;
    }
    else {
        for (size_t i = 0; i < services.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << services[i] << std::endl;
        }
    }
}

void RoomCategory::setServices(const std::vector<std::string>& newServices) {
    services = newServices;
}

std::string RoomCategory::toString() const {
    std::string result = std::to_string(id) + "," + name + "," + description + ",";
    for (size_t i = 0; i < services.size(); ++i) {
        result += services[i];
        if (i != services.size() - 1)
            result += ";";
    }
    return result;
}

RoomCategory RoomCategory::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string idStr, name, description, servicesStr;
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, description, ',');
    std::getline(ss, servicesStr); // Остаток строки - это сервисы

    int id = 0;
    if (!idStr.empty()) id = std::stoi(idStr);

    std::vector<std::string> servs;
    std::stringstream servStream(servicesStr);
    std::string service;
    while (std::getline(servStream, service, ';')) {
        if (!service.empty()) servs.push_back(service);
    }
    return RoomCategory(id, name, description, servs);
}