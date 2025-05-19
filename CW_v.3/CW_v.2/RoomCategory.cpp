#include "RoomCategory.h"

using namespace std;
int RoomCategory::categoryCounter = 1; // Инициализация

RoomCategory::RoomCategory(int i, string name, string description, vector<string> services)
    : id(i), name(move(name)), description(move(description)), services(move(services)) {
    if (i >= categoryCounter) categoryCounter = i + 1;
}

int RoomCategory::getId() const { return id; }
string RoomCategory::getName() const { return name; }
string RoomCategory::getDescription() const { return description; }

const vector<string>& RoomCategory::getServicesList() const {
    return services;
}

void RoomCategory::printServices() const {
    if (services.empty()) {
        cout << "  (нет услуг)" << endl;
    }
    else {
        for (size_t i = 0; i < services.size(); ++i) {
            cout << "  " << (i + 1) << ". " << services[i] << endl;
        }
    }
}

void RoomCategory::setServices(const vector<string>& newServices) {
    services = newServices;
}

string RoomCategory::toString() const {
    string result = to_string(id) + "," + name + "," + description + ",";
    for (size_t i = 0; i < services.size(); ++i) {
        result += services[i];
        if (i != services.size() - 1)
            result += ";";
    }
    return result;
}

RoomCategory RoomCategory::fromString(const string& line) {
    stringstream ss(line);
    string idStr, name, description, servicesStr;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, description, ',');
    getline(ss, servicesStr); // Остаток строки - это сервисы

    int id = 0;
    if (!idStr.empty()) id = stoi(idStr);

    vector<string> servs;
    stringstream servStream(servicesStr);
    string service;
    while (getline(servStream, service, ';')) {
        if (!service.empty()) servs.push_back(service);
    }
    return RoomCategory(id, name, description, servs);
}